/*
 * GaussianSpace.h
 *
 *  Created on: Mar 28, 2017
 *      Author: paco
 */

#ifndef SRC_GAUSSIANSPACE_H_
#define SRC_GAUSSIANSPACE_H_

#include "PersonnalSocialSpace.h"

#include <Eigen/Dense>

using namespace Eigen;

class GaussianSpace: public PersonnalSocialSpace {
public:
	// --- CONSTRUCTOR & DESTRUCTOR
	GaussianSpace(Agent * a, int id=0);
	virtual ~GaussianSpace();

	// --- METHOD
	double phi(Vector3d testedRealPoint);

};

#endif /* SRC_GAUSSIANSPACE_H_ */
