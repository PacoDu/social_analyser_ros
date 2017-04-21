/*
 * GroupSocialSpace.h
 *
 *  Created on: Mar 29, 2017
 *      Author: paco
 */

#ifndef GROUPSOCIALSPACE_H_
#define GROUPSOCIALSPACE_H_

#include "SocialSpace.h"
#include "../genericType/AgentContainer.h"

class GroupSocialSpace: public SocialSpace, public AgentContainer {
public:
	// --- CONSTRUCTOR & DESTRUCTOR
	GroupSocialSpace(int id = 0);
	GroupSocialSpace(std::vector<Agent*>& a, int id = 0);
	virtual ~GroupSocialSpace();

};

#endif /* GROUPSOCIALSPACE_H_ */
