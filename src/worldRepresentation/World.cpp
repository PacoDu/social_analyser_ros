/*
 * World.cpp
 *
 *  Created on: Mar 29, 2017
 *      Author: paco
 */

#include "World.h"
// #include "ofMain.h"

World::World(double w, double h, int wv, int hv, Vector3d position, double theta):
		DrawnObject(position,theta), width(w), height(h), widthView(wv), heightView(hv){
}

World::~World() {
	// TODO Auto-generated destructor stub
}

// void World::draw(World* world) {
// 	// TODO dirty
// 	this->draw();
// }

// void World::draw(){
// 	ofNoFill();
// 	ofDrawRectangle(this->getX(), this->getY(), this->widthView, this->heightView);
// 	ofFill();
// }
