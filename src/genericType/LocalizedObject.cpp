/*
 * LocalizedObject.cpp
 *
 *  Created on: Mar 27, 2017
 *      Author: paco
 */

#include "LocalizedObject.h"

// --- CONSTRUCTOR & DESTRUCTOR
LocalizedObject::LocalizedObject(Vector3d p, double theta): position(p), theta(fmod(theta,2*M_PI)) {
}

LocalizedObject::~LocalizedObject() {
}

// --- Getter & Setter
Vector3d LocalizedObject::getPosition() const {
	return position;
}

void LocalizedObject::setPosition(Vector3d position) {
	this->position = position;
}

double LocalizedObject::getTheta() const {
	return theta;
}

void LocalizedObject::setTheta(double theta) {
	this->theta = fmod(theta,2*M_PI);
}

Vector3d LocalizedObject::getDirection() {
	Rotation2Dd t(this->theta);
	Vector2d tmp = t*Vector2d::UnitX();
	return Vector3d(tmp.x(), tmp.y(), 0);
}

double LocalizedObject::getX() const {
	return this->position.x();
}

void LocalizedObject::setX(double x) {
	this->position.x() = x;
}

double LocalizedObject::getY() const {
	return this->position.y();
}

void LocalizedObject::setY(double y) {
	this->position.y() = y;
}
