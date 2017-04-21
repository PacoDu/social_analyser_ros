/*
 * GroupSocialSpace.cpp
 *
 *  Created on: Mar 29, 2017
 *      Author: paco
 */

#include "GroupSocialSpace.h"

// --- CONSTRUCTOR & DESTRUCTOR
GroupSocialSpace::GroupSocialSpace(int id):
		SocialSpace(id), AgentContainer(){
}
GroupSocialSpace::GroupSocialSpace(std::vector<Agent*>& a, int id):
		SocialSpace(id), AgentContainer(a){
}

GroupSocialSpace::~GroupSocialSpace() {
	// TODO Auto-generated destructor stub
}
