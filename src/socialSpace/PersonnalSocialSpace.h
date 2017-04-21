/*
 * PersonnalSocialSpace.h
 *
 *  Created on: Mar 29, 2017
 *      Author: paco
 */

#ifndef PERSONNALSOCIALSPACE_H_
#define PERSONNALSOCIALSPACE_H_

#include "SocialSpace.h"
#include "../agentManagement/Agent.h"

class PersonnalSocialSpace: public SocialSpace {
public:
	// --- CONSTRUCTOR & DESTRUCTOR
	PersonnalSocialSpace(Agent * a, int id = 0);
	virtual ~PersonnalSocialSpace();

protected:
	Agent * _agent;
};

#endif /* PERSONNALSOCIALSPACE_H_ */
