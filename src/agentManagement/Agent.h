/*
 * Person.h
 *
 *  Created on: Mar 24, 2017
 *      Author: paco
 */

#ifndef SRC_AGENT_H_
#define SRC_AGENT_H_

#include "../genericType/IdentifiedObject.h"
#include "../genericType/DrawnObject.h"

class Formation;
class GaussianSpace;

class Agent: public IdentifiedObject, public DrawnObject {
public:
	// --- CONSTRUCTOR & DESTRUCTOR
	Agent(Vector3d p = Vector3d(), double theta=0, int id=0);
	~Agent();

	// --- METHOD
	Agent * findNearestNeighbor(std::vector<Agent*> agents);
	void draw(World* world);
	Vector3d* getFOVIntersection(Agent * a);

	// --- Getter & Setter
	GaussianSpace* getSocialSpace() const;
	void setSocialSpace(GaussianSpace* socialSpace);

protected:
	GaussianSpace* pSocialSpace;
};

#endif /* SRC_AGENT_H_ */
