/*
 * GridCell.cpp
 *
 *  Created on: Apr 6, 2017
 *      Author: paco
 */

#include "GridCell.h"
// #include "ofMain.h"

GridCell::GridCell(double size, double value, Vector3d p, int id):
	IdentifiedObject(id), DrawnObject(p), _size(size), _value(value) {
	assert(value <= 255 && value >= 0);
}

GridCell::~GridCell() {
	// TODO Auto-generated destructor stub
}

double GridCell::getValue() const {
	return _value;
}

// void GridCell::draw(World* world) {
// 	Vector3d pView = real_to_pixel(world, this->getPosition());
// 	Vector3d sView = real_to_pixel(world, Vector3d(this->getX()+this->_size, 0, 0));
//
// 	ofPushMatrix();
// 		ofTranslate(pView.x(), pView.y());
// 		ofRotateZ(ofRadToDeg(this->getTheta()));
// 		ofSetColor((int)_value,(int)_value, (int)_value);
// 		ofFill();
// 		ofDrawRectangle(0,0, sView.x()-pView.x(), sView.x()-pView.x());
// //		ofSetColor(255, 255, 255);
// //		ofNoFill();
// //		ofSetLineWidth(0.05);
// //		ofDrawRectangle(0,0, sView.x-pView.x, sView.x-pView.x);
// 	ofPopMatrix();
// }

void GridCell::setValue(double value) {
	_value = value;
}

double GridCell::getSize() const {
	return _size;
}

void GridCell::setSize(double size) {
	_size = size;
}
