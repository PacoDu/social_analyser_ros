/*
 * GroupDetector.h
 *
 *  Created on: Apr 10, 2017
 *      Author: paco
 */

#ifndef SRC_GROUPDETECTOR_H_
#define SRC_GROUPDETECTOR_H_

#include "../agentManagement/Population.h"
#include "../agentManagement/Agent.h"

#include <Eigen/Dense>

using namespace Eigen;

class GroupDetector {
public:
	GroupDetector(Population* pop);
	virtual ~GroupDetector();

	void detect();
	void checkExistingFormation();

protected:
	Population* _population;
	//dirty
	int formationId = 0;
};

#endif /* SRC_GROUPDETECTOR_H_ */
