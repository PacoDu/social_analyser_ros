/*
 * UDPServer.cpp
 *
 *  Created on: Apr 19, 2017
 *      Author: paco
 */

#include "UDPServer.h"
#include <stdio.h>
#include <string.h>

#include <Eigen/Dense>

using namespace Eigen;
UDPServer::UDPServer(int port): portNumber(port) {
	//---- create UDP socket ----
	udpReceiveSocket = socket(PF_INET,SOCK_DGRAM,0);
	udpSendSocket = socket(PF_INET,SOCK_DGRAM,0);

	// Init myAddr struct
	myAddr.sin_family=AF_INET;
	myAddr.sin_port=htons(portNumber);
	myAddr.sin_addr.s_addr=htonl(INADDR_ANY);

	// Bind to port
	bind(udpReceiveSocket, (struct sockaddr *)&myAddr, sizeof(myAddr));

	printf("UDP Server started on port: %d\n", portNumber);


	pop = new Population();
	gd = new GroupDetector(pop);
}

UDPServer::~UDPServer() {
	// TODO Auto-generated destructor stub
}

int UDPServer::do_read() {
	socklen_t len = sizeof(fromAddr);

	// Read 122 bytes
	int ret = recvfrom(udpReceiveSocket, &recvBuffer, recvBuffer_size, 0, (struct sockaddr *)&fromAddr, &len);

	if(ret > 0){
		printf("Received frame type#%u from %s:%d\n",
				recvBuffer[0], inet_ntoa(fromAddr.sin_addr), ntohs(fromAddr.sin_port));
	}else{
		printf("Socket shutdown or error while reading socket");
	}

	return ret;
}

int UDPServer::do_send(uint8_t * sendBuffer, int sendBuffer_size) {
	struct sockaddr_in toAddr;
	toAddr.sin_family = AF_INET;
	toAddr.sin_port = htons(portNumber);
	toAddr.sin_addr = fromAddr.sin_addr;

	int ret = sendto(udpSendSocket, sendBuffer, sendBuffer_size, 0, (struct sockaddr *)&toAddr, sizeof(toAddr));

	printf("Replied to client: %s:%d\n", inet_ntoa(toAddr.sin_addr), toAddr.sin_port);
	return ret;
}

int UDPServer::parse() {
	// Parse buffer depending on frame type
	switch(recvBuffer[0]){
		case 0:
			return parse_frame0();
			break;
		default:
			printf("Unknown frame type: %d, parsing failed\n", recvBuffer[0]);
			return 0;
			break;

	}
}

int UDPServer::parse_frame0() {
	int n = recvBuffer[1];
	pop->clearAgents(); // TODO update existing agents
	pop->clearFormations();

	for(unsigned int i = 2; i < 2+n*20; i+=20){
		int id;
		float x, y, z, theta;
		int tx, ty, tz, ttheta;

		memcpy(&id, &recvBuffer[i], sizeof(id));
		tx = recvBuffer[i+4]<<24|recvBuffer[i+5]<<16|recvBuffer[i+6]<<8|recvBuffer[i+7];
		ty = recvBuffer[i+8]<<24|recvBuffer[i+9]<<16|recvBuffer[i+10]<<8|recvBuffer[i+11];
		tz = recvBuffer[i+12]<<24|recvBuffer[i+13]<<16|recvBuffer[i+14]<<8|recvBuffer[i+15];
		ttheta = recvBuffer[i+16]<<24|recvBuffer[i+17]<<16|recvBuffer[i+18]<<8|recvBuffer[i+19];
		memcpy(&x, &tx, sizeof(x));
		memcpy(&y, &ty, sizeof(y));
		memcpy(&z, &tz, sizeof(z));
		memcpy(&theta, &ttheta, sizeof(theta));

		id = ntohl(id);
		printf("Parsed Agent#%d (%.2f,%.2f,%.2f) theta=%.2f\n", id, x, y, z, theta);


		updateOrPushAgent(id, x, y, z, theta);
	}

	if(n>0)
		gd->detect();

	return n;
}

int UDPServer::send_frame1() {
	uint8_t sendBuffer[9] = {0}; // T(Bytes) | x(float) | y(float)

	// set Frame type
	sendBuffer[0] = 1;

	// fill frame
	float x = 0, y=0;
	if(pop->getFormations().size() > 0){
		x = (float)pop->getFormations()[0]->getSocialSpace()->getCenter().x();
		y = (float)pop->getFormations()[0]->getSocialSpace()->getCenter().y();
	}

	memcpy(&sendBuffer[1], &x, sizeof(x));
	memcpy(&sendBuffer[5], &y, sizeof(y));

	printf("Sending frame#1 center(%.2f,%.2f)\n", x, y);

	do_send(sendBuffer, 9);

	return 0;
}

int UDPServer::send_frame2() {
	uint8_t sendBuffer[9] = {0}; // T(Bytes) | x(float) | y(float)

	// set Frame type
	sendBuffer[0] = 2;

	// fill frame
	float x = 0, y=0;
	if(pop->getFormations().size() > 0){
		x = (float)pop->getFormations()[0]->getInteractionPosition().x();
		y = (float)pop->getFormations()[0]->getInteractionPosition().y();
	}

	memcpy(&sendBuffer[1], &x, sizeof(x));
	memcpy(&sendBuffer[5], &y, sizeof(y));

	printf("Sending frame#2 center(%.2f,%.2f)\n", x, y);

	do_send(sendBuffer, 9);

	return 0;
}

void UDPServer::run() {
	while(1){
		do_read();
		parse();
		send_frame1();
		send_frame2();
	}
}

void UDPServer::updateOrPushAgent(int id, float x, float y, float z,
		float theta) {
	Agent* a = pop->getAgent(id);
	if(a){
		a->setX(x);
		a->setY(y);
//		a->setZ(z); TODO
		a->setTheta(theta);
	}
	else{
		a = new Agent(Vector3d(x, y, z), theta, id);
		pop->pushAgent(a);
	}
}
