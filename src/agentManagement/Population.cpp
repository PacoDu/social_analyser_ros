/*
 * Population.cpp
 *
 *  Created on: Mar 24, 2017
 *      Author: paco
 */

#include "Population.h"
// #include "ofMain.h"

// --- CONSTRUCTOR & DESTRUCTOR
Population::Population(Vector3d p, int id):
		IdentifiedObject(id), DrawnObject(p), AgentContainer() {
}

Population::Population(std::vector<Agent*> a, Vector3d p, int id):
		IdentifiedObject(id), DrawnObject(p), AgentContainer(a){
}

Population::~Population() {
	for(unsigned int i=0; i<this->_formations.size(); i++){
		delete this->_formations[i];
	}

	for(unsigned int i=0; i<this->_agents.size(); i++){
		delete this->_agents[i];
	}
}

// --- METHOD
// void Population::draw(World* world) {
// 	std::stringstream ss;
//
// 	for(unsigned int i=0; i<_formations.size(); i++){
// 		ss << "Formation #" << _formations[i]->getId() << ": ";
// 				for(unsigned int k = 0; k < _formations[i]->getSocialSpace()->getAgents().size(); k++){
// 					ss << "Agent#" <<  _formations[i]->getSocialSpace()->getAgents()[k]->getId() << ", ";
// 				}
// 				ss << " interactionPotential=" << _formations[i]->getInteractionPotential()	<< std::endl;
//
// 		_formations[i]->draw(world);
// 	}
//
// 	for(unsigned int i=0; i<this->_agents.size(); i++){
// 		ss << "Agent #" << this->_agents[i]->getId()
// 				<< ": x = " << this->_agents[i]->getX()
// 				<< ", y = " << this->_agents[i]->getY()
// 				<< ", Theta = " << this->_agents[i]->getTheta()
// 				<< ", Theta (degres) = " << ofRadToDeg(this->_agents[i]->getTheta()) << std::endl;
//
// 		this->_agents[i]->draw(world);
// 	}
//
// 	ofSetHexColor(0x2C291F);
// 	ofDrawBitmapString(ss.str(), world->getX(), world->getY()+world->heightView+20);
// }

void Population::clear() {
	for(unsigned int i=0; i<this->_agents.size(); i++){
		delete this->_agents[i];
	}

	this->_agents.clear();

	for(unsigned int i=0; i<_formations.size(); i++){
		delete _formations[i];
	}

	this->_formations.clear();

	// ofLogNotice("Population::clear") << "Population#" << this->getId() << " cleared";
}


void Population::pushFormation(Formation* f) {
	_formations.push_back(f);
}

int Population::removeFormation(unsigned int formationId) {
	for(unsigned int i=0; i<_formations.size(); i++){
		if(_formations[i]->getId() == formationId) {
			_formations.erase(_formations.begin()+i);
			return 0;
		}
	}
	return -1;
}

void Population::clearFormations() {
	_formations.clear();
}

int Population::isGrouped(Agent* a) {
	return this->isGrouped(a->getId());
}

int Population::isGrouped(unsigned int agentId) {
	for(unsigned int i = 0; i < this->_formations.size(); i++){
		if(this->_formations[i]->isInFormation(agentId)){
			return 1;
		}
	}
	return 0;
}

Formation* Population::getRelatedFormation(unsigned int agentId) {
	for(unsigned int i = 0; i < this->_formations.size(); i++){
		if(this->_formations[i]->isInFormation(agentId)){
			return this->_formations[i];
		}
	}
	return NULL;
}

Formation* Population::getRelatedFormation(Agent* a) {
	return this->getRelatedFormation(a->getId());
}

// --- Getter & Setter
const std::vector<Formation*>& Population::getFormations() const {
	return _formations;
}

void Population::setFormations(const std::vector<Formation*>& formations) {
	_formations = formations;
}
