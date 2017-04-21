#include "ros/ros.h"
#include <geometry_msgs/PoseStamped.h>

#include <cstdlib>
#include <Eigen/Dense>

#include "agentManagement/Agent.h"

using namespace Eigen;

int main(int argc, char **argv)
{
  ros::init(argc, argv, "pepper_social_navigation_simple_node");
  if (argc != 3){
    ROS_INFO("usage: pepper_social_navigation_simple_node X Y");
    return 1;
  }

  ros::NodeHandle n;
  ros::Publisher goal_pub = n.advertise<geometry_msgs::PoseStamped>("/move_base_simple/goal", 1);

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

  goal.pose.position.x = atoll(argv[1]);
  goal.pose.position.y = atoll(argv[2]);
  goal.pose.orientation.w = 1.0;

  goal_pub.publish(goal);

  ros::Duration(5).sleep();


  ROS_INFO("Sending 2nd message to move_base_simple");
  goal_pub.publish(goal);
  ROS_INFO("Hello world!");

  Agent * a = new Agent(Vector3d(1,2,0));

  ROS_INFO("Succesfully created an Agent at (%f,%f)", a->getX(), a->getY());

  return 0;
}
