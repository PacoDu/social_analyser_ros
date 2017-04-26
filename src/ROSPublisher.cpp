/*
 * ROSPublisher.cpp
 *
 *  Created on: Apr 20, 2017
 *      Author: paco
 */

#include "ROSPublisher.h"

ROSPublisher::ROSPublisher() {
	ros::init(argc, argv, "pepper_social_navigation_simple_node");
  goal_pub = n.advertise<geometry_msgs::PoseStamped>(MOVE_BASE_SIMPLE_TOPIC, 1);
}

ROSPublisher::~ROSPublisher() {
	// TODO Auto-generated destructor stub
}

void moveFor(float x, float y){
	ros::Rate poll_rate(100);

  // Wait for connection
  while(goal_pub.getNumSubscribers() == 0){
    ROS_INFO("Waiting for connection");
    poll_rate.sleep();
  }

  ROS_INFO("Sending message to move_base_simple");

  geometry_msgs::PoseStamped goal;
  goal.header.frame_id = "base_footprint";
  goal.header.stamp = ros::Time::now();

  goal.pose.position.x = x;
  goal.pose.position.y = y;
  goal.pose.orientation.w = 1.0;

  goal_pub.publish(goal);
}
