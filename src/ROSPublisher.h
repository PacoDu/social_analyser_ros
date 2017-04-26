/*
 * ROSPublisher.h
 *
 *  Created on: Apr 20, 2017
 *      Author: paco
 */

#ifndef SRC_ROSPUBLISHER_H_
#define SRC_ROSPUBLISHER_H_

#include "ros/ros.h"
#include <geometry_msgs/PoseStamped.h>

#include "config.h"

class ROSPublisher {
public:
	ROSPublisher(int port);
	virtual ~ROSPublisher();

	void moveFor(float x, float y);

protected:
	ros::NodeHandle n;
	ros::Publisher goal_pub;
};

#endif /* SRC_ROSPUBLISHER_H_ */
