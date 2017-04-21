/*
 * AgentContainer.cpp
 *
 *  Created on: Mar 27, 2017
 *      Author: paco
 */

#include "AgentContainer.h"

// --- CONSTRUCTOR & DESTRUCTOR
AgentContainer::AgentContainer() {
}

AgentContainer::AgentContainer(std::vector<Agent*>& agents) {
	_agents = agents;
}

AgentContainer::~AgentContainer() {
}

// --- METHOD
int AgentContainer::removeAgent(unsigned int agentId) {
	for(unsigned int i=0; i<_agents.size(); i++){
		if(_agents[i]->getId() == agentId) {
			_agents.erase(_agents.begin()+i);
			return 0;
		}
	}

	return -1;
}

void AgentContainer::pushAgent(Agent* p) {
	this->_agents.push_back(p);
}

Agent* AgentContainer::getAgent(unsigned int agentId) {
	for(unsigned int i=0; i<_agents.size(); i++){
		if(_agents[i]->getId() == agentId) {
			return _agents[i];
		}
	}

	return NULL;
}

void AgentContainer::clearAgents() {
	_agents.clear();
}

// Getter & Setter
std::vector<Agent*> AgentContainer::getAgents() {
	return this->_agents;
}

void AgentContainer::setAgents(const std::vector<Agent*>& agents) {
	_agents = agents;
}
