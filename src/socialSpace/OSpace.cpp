/*
 * OSpace.cpp
 *
 *  Created on: Mar 27, 2017
 *      Author: paco
 */

#include "OSpace.h"
#include "../utils.h"
// #include "ofMain.h"

// --- CONSTRUCTOR & DESTRUCTOR
OSpace::OSpace(std::vector<Agent*>& a, int id): GroupSocialSpace(a, id), DrawnObject(){
	this->update();
}

OSpace::OSpace(int id): GroupSocialSpace(id){
}

OSpace::~OSpace() {
	// TODO Auto-generated destructor stub
}

// --- METHOD
void OSpace::update() {
	this->intersectionPoints.resize(this->_agents.size());
	this->centroids.resize(this->_agents.size());
	this->intersectionPoints.clear();
	this->centroids.clear();

	this->computegCenter();
	this->sortAgents();
	this->computeCentroids();
	this->computeCovarMatrix();
}


// void OSpace::draw(World* world) {
// 	Vector3d pView = real_to_pixel(world, center);
// 	ofPushMatrix();
// 		ofSetHexColor(0xd896ff);
// 		ofTranslate(pView.x(), pView.y());
// 		ofDrawCircle(0, 0, 10);
// 	ofPopMatrix();
//
// 	pView = real_to_pixel(world, gCenter);
// 	ofPushMatrix();
// 		ofSetHexColor(0x0000ff);
// 		ofTranslate(pView.x(), pView.y());
// 		ofDrawCircle(0, 0, 10);
// 	ofPopMatrix();
//
//
// 	for(unsigned int i=0; i < intersectionPoints.size(); i++){
// 		pView = real_to_pixel(world, intersectionPoints[i]);
// 		ofPushMatrix();
// 			ofSetHexColor(0xAFAFAF);
// 			ofTranslate(pView.x(), pView.y());
// 			ofDrawCircle(0, 0, 6);
// 		ofPopMatrix();
// 	}
//
// 	for(unsigned int i=0; i < centroids.size(); i++){
// 		pView = real_to_pixel(world, centroids[i]);
// 		ofPushMatrix();
// 			ofSetHexColor(0xFF0000);
// 			ofTranslate(pView.x(), pView.y());
// 			ofDrawCircle(0, 0, 6);
// 		ofPopMatrix();
// 	}
// }

// Getter & Setter
void OSpace::computegCenter() {
	this->gCenter << 0,0,0 ;
	for(unsigned int i=0; i < this->_agents.size(); i++){
		this->gCenter += this->_agents[i]->getPosition();
	}

	this->gCenter /= this->_agents.size();
}

void OSpace::sortAgents() {
//	if(this->_agents.size() > 2){
//
//	}
	bool shifted = false;
	for(unsigned int i=0; i < this->_agents.size()-1; i++){
		bool test = less(_agents[i]->getPosition(), _agents[i+1]->getPosition());
		if(test){
			Agent* tmp = _agents[i];
			_agents[i] = _agents[i+1];
			_agents[i+1] = tmp;

			shifted = true;
		}
	}

//	for(unsigned int i=0; i < this->_agents.size(); i++){
//		_agents[i]->setId(i);
//	}

	if(shifted) this->sortAgents();
	else{
		// ofLogNotice("OSpace::sortAgents") << "Agents sorted conter clock wise";
		for(unsigned int i=0; i < this->_agents.size(); i++){
			// ofLogNotice("OSpace::sortAgents") << i << ": Agent#" << this->_agents[i]->getId();
		}
	}
}

bool OSpace::less(Vector3d a, Vector3d b)
{
    if (a.x() - gCenter.x() >= 0 && b.x() - gCenter.x() < 0)
        return true;
    if (a.x() - gCenter.x() < 0 && b.x() - gCenter.x() >= 0)
        return false;
    if (a.x() - gCenter.x() == 0 && b.x() - gCenter.x() == 0) {
        if (a.y() - gCenter.y() >= 0 || b.y() - gCenter.y() >= 0)
            return a.y() > b.y();
        return b.y() > a.y();
    }

    // compute the cross product of vectors (center -> a) x (center -> b)
    int det = (a.x() - gCenter.x()) * (b.y() - gCenter.y()) - (b.x() - gCenter.x()) * (a.y() - gCenter.y());
    if (det < 0)
        return true;
    if (det > 0)
        return false;

    // Points a and b are on the same line from the center
    // check which Point is closer to the center
    int d1 = (a.x() - gCenter.x()) * (a.x() - gCenter.x()) + (a.y() - gCenter.y()) * (a.y() - gCenter.y());
    int d2 = (b.x() - gCenter.x()) * (b.x() - gCenter.x()) + (b.y() - gCenter.y()) * (b.y() - gCenter.y());
    return d1 > d2;
}

// Without rotation
//double OSpace::phi(Vector3d testedRealPoint) {
//	Vector2d v = (testedRealPoint-center).head<2>();
//
//	Matrix<double, 1, 2> i = v.transpose()*covarMatrix.inverse();
//
//	double j =i*v;
//
//	return exp(-0.5*j);
//}

double OSpace::phi(Vector3d testedRealPoint) {
	Vector2d v = (testedRealPoint-center).head<2>();

	Vector2d H1n;
	H1n <<
			(this->_agents[0]->getX() + this->_agents[this->_agents.size()-1]->getX())/2,
			(this->_agents[0]->getY() + this->_agents[this->_agents.size()-1]->getY())/2;

	Vector2d u1;
	u1 <<
			this->center.x() - H1n.x(),
			this->center.y() - H1n.y();

	Vector2d u2;
	u2 <<
			this->_agents[0]->getX() - H1n.x(),
			this->_agents[0]->getY() - H1n.y();

	u1.normalize();
	u2.normalize();

	Matrix<double, 2, 2> P;
	P <<
			u1.x(), u2.x(),
			u1.y(), u2.y();

	v = P.inverse() * v;

	Matrix<double, 1, 2> i = v.transpose()*covarMatrix.inverse();

	double j =i*v;

	return exp(-0.5*j);
}

// Real math from Gomez paper
void OSpace::computeCovarMatrix() {

	double dh = distance(_agents[_agents.size()-1]->getPosition(), _agents[0]->getPosition());
	for(unsigned int i=0; i < _agents.size()-1; i++){
		dh += distance(_agents[i+1]->getPosition(), _agents[i]->getPosition());
	}
	dh /= _agents.size();

	double di = distance(centroids[centroids.size()-1], _agents[_agents.size()-1]->getPosition()-_agents[0]->getPosition());
	//double di = sqrt((centroids[centroids.size()-1].x() - centroids[0].x())*(centroids[centroids.size()-1].x() - centroids[0].x()) + (centroids[centroids.size()-1].y() - centroids[0].y())*(centroids[centroids.size()-1].y() - centroids[0].y()));
	for(unsigned int i=0; i < centroids.size()-1; i++){
		//di += sqrt((centroids[i+1].x() - centroids[i].x())*(centroids[i+1].x() - centroids[i].x()) + (centroids[i+1].y() - centroids[i].y())*(centroids[i+1].y() - centroids[i].y()));
		di += distance(centroids[i], _agents[i]->getPosition()-_agents[i+1]->getPosition());
	}
	di /= centroids.size();
	di *= 2;

	this->covarMatrix <<
//						dh/4*dh/4, 0,
//						0, di/2*di/2;
						dh/4, 0,
						0, di/2;

	// ofLogNotice("OSpace::computeCovarMatrix") << "Covariance matrix computed for Formation#" << this->getId() << ":" << std::endl << this->covarMatrix;
}

// Old version wrong math
//void OSpace::computeCovarMatrix() {
//	double dh = sqrt((_agents[_agents.size()-1]->getX() - _agents[0]->getX())*(_agents[_agents.size()-1]->getX() - _agents[0]->getX()) + (_agents[_agents.size()-1]->getY() - _agents[0]->getY())*(_agents[_agents.size()-1]->getY() - _agents[0]->getY()));
//	for(unsigned int i=1; i < _agents.size()-1; i++){
//		dh += sqrt((_agents[i+1]->getX() - _agents[i]->getX())*(_agents[i+1]->getX() - _agents[i]->getX()) + (_agents[i+1]->getY() - _agents[i]->getY())*(_agents[i+1]->getY() - _agents[i]->getY()));
//	}
//	dh /= _agents.size();
//
//	// TODO di = 0 when agents.size = 2
//	double di = sqrt((centroids[centroids.size()-1].x() - centroids[0].x())*(centroids[centroids.size()-1].x() - centroids[0].x()) + (centroids[centroids.size()-1].y() - centroids[0].y())*(centroids[centroids.size()-1].y() - centroids[0].y()));
//	for(unsigned int i=1; i < centroids.size()-1; i++){
//		di += sqrt((centroids[i+1].x() - centroids[i].x())*(centroids[i+1].x() - centroids[i].x()) + (centroids[i+1].y() - centroids[i].y())*(centroids[i+1].y() - centroids[i].y()));
//	}
//	di /= centroids.size();
//	di *= 2;
//
//	this->covarMatrix <<
//						dh/4, 0,
//						0, di/2;
//}

void OSpace::computeCentroids() {
	intersectionPoints.resize(_agents.size());
	centroids.resize(_agents.size());

	Vector3d realCenter;
	int n = 0;

	for(unsigned int i=0; i < this->_agents.size(); i++){

		unsigned int neighborIndex = i+1;
		if(neighborIndex >= this->_agents.size()) neighborIndex = 0;

		Vector3d* intersec = _agents[i]->getFOVIntersection(_agents[neighborIndex]);
		if(intersec){
			// ofLogNotice("OSpace::computeCentroids") << "Agent#" << _agents[i]->getId() << " FOV intersection with Agent#" << _agents[neighborIndex]->getId();
			n++; // dirty use push back and vector size (clash with resize if there is no intersect)
			intersectionPoints[i] = *intersec;
			// compute centroïds
			Vector3d centro;
			centro.x() = (intersectionPoints[i].x() + ((_agents[neighborIndex]->getX() + _agents[i]->getX())/2))/2;
			centro.y() = (intersectionPoints[i].y() + ((_agents[neighborIndex]->getY() + _agents[i]->getY())/2))/2;
			centroids[i] = centro;
			realCenter += centro;
		}
	}

	if(n!=0)
		realCenter /=  n;

	center << realCenter.x(), realCenter.y(), realCenter.z();
}

Vector3d OSpace::getCenter() const {
	return center;
}

void OSpace::setCenter(const Vector3d& center) {
	this->center = center;
}

Vector3d OSpace::getgCenter() const {
	return gCenter;
}

void OSpace::setgCenter(const Vector3d& gCenter) {
	this->gCenter = gCenter;
}
