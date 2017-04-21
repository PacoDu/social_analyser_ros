/*
 * Person.cpp
 *
 *  Created on: Mar 24, 2017
 *      Author: paco
 */

#include "Agent.h"
#include "Formation.h"
#include "../socialSpace/GaussianSpace.h"
#include <limits>
#include "../utils.h"
// #include "ofMain.h"

// --- CONSTRUCTOR & DESTRUCTOR
Agent::Agent(Vector3d p, double theta, int id):
		IdentifiedObject(id), DrawnObject(p,theta) {

	pSocialSpace = new GaussianSpace(this);
}

Agent::~Agent() {
	delete this->pSocialSpace;
}

// --- METHOD
// void Agent::draw(World * world) {
// 	Vector3d pView = real_to_pixel(world, this->getPosition());
// 	ofPushMatrix();
// 		ofSetHexColor(0x6497b1);
// 		ofTranslate(pView.x(), pView.y());
// 		ofRotateZ(ofRadToDeg(this->getTheta()));
//
// 		ofDrawBitmapString("#"+ofToString(this->getId()), -10, -20);
// 		ofDrawTriangle(0, 10, 25, 0, 0, -10);
//
// //		ofSetHexColor(0x011f4b);
// 		ofSetHexColor(0xFFFFFF);
// 		ofDrawCircle(0,0,5);
// 		ofSetHexColor(0xFF0000);
// 		ofDrawCircle(0,0,1);
// 	ofPopMatrix();
// }

Agent* Agent::findNearestNeighbor(std::vector<Agent*> agents) {
	// TODO use kd tree ?
	double min_distance = std::numeric_limits<double>::infinity();
	Agent * a;
	for(unsigned int i = 0; i < agents.size(); i++){
		if(agents[i]->getId() != this->getId()){
			double computedDist = distance(this->position, agents[i]->getPosition());
			if(computedDist < min_distance){
				min_distance = computedDist;
				a = agents[i];
			}
		}
	}
	return a;
}

Vector3d* Agent::getFOVIntersection(Agent* a) {
	// Return FOV intersection point or NULL if
	Vector3d* intersec = rayIntersectionPoint(this->getPosition(), this->getDirection(), a->getPosition(), a->getDirection());
	if(!intersec){
		// Agents are parallels or do not intersect
		if(fmod(a->getTheta()+M_PI,2*M_PI) == this->getTheta()){
			// Agents are face to face return middle point
			intersec = new Vector3d((this->getPosition()+a->getPosition())/2);
		}
	}

	return intersec;
}

// --- Getter & Setter
GaussianSpace* Agent::getSocialSpace() const {
	return pSocialSpace;
}

void Agent::setSocialSpace(GaussianSpace* socialSpace) {
	pSocialSpace = socialSpace;
}
