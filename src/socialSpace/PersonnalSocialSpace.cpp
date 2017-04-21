/*
 * PersonnalSocialSpace.cpp
 *
 *  Created on: Mar 29, 2017
 *      Author: paco
 */

#include "PersonnalSocialSpace.h"
#include "../agentManagement/Agent.h"

PersonnalSocialSpace::PersonnalSocialSpace(Agent* a, int id):
		SocialSpace(id), _agent(a) {
}

PersonnalSocialSpace::~PersonnalSocialSpace() {
	// TODO Auto-generated destructor stub
}
