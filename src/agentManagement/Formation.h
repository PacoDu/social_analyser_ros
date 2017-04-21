/*
 * Formation.h
 *
 *  Created on: Mar 24, 2017
 *      Author: paco
 */

#ifndef SRC_FORMATION_H_
#define SRC_FORMATION_H_

#include "Agent.h"
#include "../genericType/IdentifiedObject.h"
#include "../genericType/DrawnObject.h"
#include "../genericType/AgentContainer.h"
#include "../socialSpace/OSpace.h"
//#include "PSpace.h"
#include "../worldRepresentation/World.h"

// TODO Remove drawnobject formation, only map will be a drawnobject
class Formation: public IdentifiedObject, public DrawnObject, public AgentContainer {
public:
	// --- CONSTRUCTOR & DESTRUCTOR
	Formation(std::vector<Agent*> a, int id=0);
	Formation(Agent* a, int id=0);
	Formation(int id=0);

	~Formation();

	// --- METHOD
	void draw(World* world);
	void update();
	void pushAgent(Agent* a);
	void removeAgent(unsigned int agentId);
	int isInFormation(Agent* a);
	int isInFormation(unsigned int agentId);
	std::vector<Agent *> initAgent(Agent * a);
	void computeInteractionPotential();
	void findInteractionPosition();


	// Getters & Setters
	OSpace* getSocialSpace() const;
	void setSocialSpace(OSpace* socialSpace);
	double getInteractionPotential() const;
	void setInteractionPotential(double interactionPotential = 0);
	const Vector3d& getInteractionPosition() const;
	void setInteractionPosition(const Vector3d& interactionPosition);

protected:
	OSpace* _socialSpace;
	double interactionPotential = 0;
	Vector3d interactionPosition;
	std::vector<Vector3d> agentDir_ospace;
	Vector3d interactionDirection;
};


#endif /* SRC_FORMATION_H_ */
