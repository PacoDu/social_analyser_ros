/*
 * Population.h
 *
 *  Created on: Mar 24, 2017
 *      Author: paco
 */

#ifndef SRC_POPULATION_H_
#define SRC_POPULATION_H_

#include "Agent.h"
#include "Formation.h"
#include "Population.h"
#include "../genericType/IdentifiedObject.h"
#include "../genericType/DrawnObject.h"
#include "../genericType/AgentContainer.h"
#include "../socialSpace/GaussianSpace.h"

class Population: public IdentifiedObject, public DrawnObject, public AgentContainer {
public:
	// --- CONSTRUCTOR & DESTRUCTOR
	Population(std::vector<Agent*> a, Vector3d p = Vector3d(), int id = 0);
	Population(Vector3d p = Vector3d(), int id = 0);
	~Population();

	// --- METHOD
	void draw(World* world);
//	void update(World* world);
	void clear();
	int isGrouped(Agent * a);
	int isGrouped(unsigned int agentId);
	Formation * getRelatedFormation(unsigned int agentId);
	Formation * getRelatedFormation(Agent* a);


	void pushFormation(Formation* f);
	int removeFormation(unsigned int formationId);
	void clearFormations();

	// --- Getter & Setter
	const std::vector<Formation*>& getFormations() const;
	void setFormations(const std::vector<Formation*>& formations);

private:
	std::vector<Formation*> _formations;
};

#endif /* SRC_POPULATION_H_ */
