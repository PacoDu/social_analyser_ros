/*
 * AgentContainer.h
 *
 *  Created on: Mar 27, 2017
 *      Author: paco
 */

#ifndef SRC_AGENTCONTAINER_H_
#define SRC_AGENTCONTAINER_H_

#include "../agentManagement/Agent.h"

class AgentContainer {
public:
	// --- CONSTRUCTOR & DESTRUCTOR
	AgentContainer();
	AgentContainer(std::vector<Agent*>& agents);
	virtual ~AgentContainer();

	// --- METHOD
	void pushAgent(Agent* a);
	int removeAgent(unsigned int agentId);
	void clearAgents();
	Agent * getAgent(unsigned int agentId);

	// Getter & Setter
	std::vector<Agent*> getAgents();
	void setAgents(const std::vector<Agent*>& agents);

protected:
	std::vector<Agent*> _agents;
};

#endif /* SRC_AGENTCONTAINER_H_ */
