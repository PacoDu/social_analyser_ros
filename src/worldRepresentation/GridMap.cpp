/*
 * GridMap.cpp
 *
 *  Created on: Apr 6, 2017
 *      Author: paco
 */

#include "GridMap.h"
#include "../utils.h"
// #include "ofMain.h"

GridMap::GridMap(World* world, Population* pop,  double resolution):
		IdentifiedObject(), DrawnObject(), _population(pop), width(world->width), height(world->height), resolution(resolution) {
	assert(fmod(width*100,resolution*100) == 0);
	assert(fmod(height*100,resolution*100) == 0);

//	_map.resize((int)(this->height/this->resolution), std::vector<GridCell*>((int)(this->width/this->resolution), ));

	for(unsigned int i=0; i < this->height/this->resolution; i++){
		std::vector<GridCell*> tmp;
		for(unsigned int j=0; j < this->width/this->resolution; j++){
			tmp.push_back(new GridCell(
					resolution, i+j,
					Vector3d(this->getX()+this->resolution*j, this->getY()+this->resolution*i, 0)
					));
		}
		_map.push_back(tmp);
	}

	update();
}

GridMap::~GridMap() {
	for(unsigned int i=0; i < this->height/this->resolution; i++){
		for(unsigned int j=0; j < this->width/this->resolution; j++){
			delete _map[i][j];
		}
	}
}

// void GridMap::draw(World* world) {
// //	Point pView = real_to_pixel(world, this->getPosition());
// //	ofPushMatrix();
// //		ofTranslate(pView.x, pView.y);
// //		ofRotateZ(ofRadToDeg(this->getTheta()));
// //	std::stringstream ss;
//
// 	for(unsigned int i=0; i < this->height/this->resolution; i++){
// 		for(unsigned int j=0; j < this->width/this->resolution; j++){
// 			_map[i][j]->draw(world);
// //			ss << "GridCell #" << _map[i][j]->getId()
// //					<< ": x = " << _map[i][j]->getX()
// //					<< ", y = " << _map[i][j]->getY() << std::endl;
// 		}
// 	}
//
//
// //	ofSetHexColor(0x2C291F);
// //	ofDrawBitmapString(ss.str(), world->getX(), world->getY()+world->heightView+100);
// //	ofPopMatrix();
// }

void GridMap::compute() {
	double min = INFINITY;
	double max = -INFINITY;
	for(unsigned int i=0; i < this->height/this->resolution; i++){
		for(unsigned int j=0; j < this->width/this->resolution; j++){
			double cellValue = 0;
			Vector3d testedPoint = _map[i][j]->getPosition();
			testedPoint.x() += _map[i][j]->getSize()/2;
			testedPoint.y() += _map[i][j]->getSize()/2;

			if(this->isPersonalSpaceEnabled()){
				for(unsigned int i = 0; i < this->_population->getAgents().size(); i++){
					cellValue += _population->getAgents()[i]->getSocialSpace()->phi(testedPoint);
				}
			}

			if(this->isGroupSpaceEnabled()){
				for(unsigned int i = 0; i < this->_population->getFormations().size(); i++){
					cellValue += _population->getFormations()[i]->getSocialSpace()->phi(testedPoint);
				}
			}

			_map[i][j]->setValue(cellValue);

			if(cellValue < min) min = cellValue;
			if(cellValue > max) max = cellValue;
		}
	}

	// ofLogNotice("GridMap::compute") << "Social map computed min=" << min << ", max=" << max;
}

void GridMap::normalize(){
	for(unsigned int i=0; i < this->height/this->resolution; i++){
		for(unsigned int j=0; j < this->width/this->resolution; j++){
			int newVal = (int)vProjection(_map[i][j]->getValue(), 0, 1, 0, 255);
			_map[i][j]->setValue(newVal);

		}
	}
}

void GridMap::update() {
	compute();
	normalize();
}

bool GridMap::isGroupSpaceEnabled() const {
	return groupSpaceEnabled;
}

void GridMap::setGroupSpaceEnabled(bool groupSpaceEnabled) {
	this->groupSpaceEnabled = groupSpaceEnabled;
}

bool GridMap::isPersonalSpaceEnabled() const {
	return personalSpaceEnabled;
}

void GridMap::setPersonalSpaceEnabled(bool personalSpaceEnabled) {
	this->personalSpaceEnabled = personalSpaceEnabled;
}
