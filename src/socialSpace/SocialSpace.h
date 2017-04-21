/*
 * SocialSpace.h
 *
 *  Created on: Mar 27, 2017
 *      Author: paco
 */

#ifndef SRC_SOCIALSPACE_H_
#define SRC_SOCIALSPACE_H_

#include "../genericType/IdentifiedObject.h"

class SocialSpace: public IdentifiedObject{
public:
	// --- CONSTRUCTOR & DESTRUCTOR
	SocialSpace(int id = 0);
	virtual ~SocialSpace();

};

#endif /* SRC_SOCIALSPACE_H_ */
