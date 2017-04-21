/*
 * UDPServer.h
 *
 *  Created on: Apr 19, 2017
 *      Author: paco
 */

#ifndef SRC_UDPSERVER_H_
#define SRC_UDPSERVER_H_

#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "agentManagement/Agent.h"
#include "agentManagement/Population.h"
#include "socialProcessing/GroupDetector.h"

class UDPServer {
public:
	UDPServer(int port);
	virtual ~UDPServer();

	int parse();
	int parse_frame0();
	int send_frame1();
	int send_frame2();
	int do_read();
	int do_send(uint8_t * sendBuffer, int sendBuffer_size);
	void run();

	void updateOrPushAgent(int id, float x, float y, float z, float theta);

protected:
	int portNumber;
	struct sockaddr_in myAddr;
	struct sockaddr_in fromAddr;

	int udpReceiveSocket;
	int udpSendSocket;

	const static int recvBuffer_size = 122;
	uint8_t recvBuffer[recvBuffer_size];

	Population* pop;
	GroupDetector* gd;
};

#endif /* SRC_UDPSERVER_H_ */
