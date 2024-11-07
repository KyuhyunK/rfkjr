#include "slros_initialize.h"

ros::NodeHandle * SLROSNodePtr;
const std::string SLROSNodeName = "rfkjr";

// For Block rfkjr/Subscribe
SimulinkSubscriber<std_msgs::Float64, SL_Bus_rfkjr_std_msgs_Float64> Sub_rfkjr_16;

// For Block rfkjr/Publish
SimulinkPublisher<std_msgs::Float64, SL_Bus_rfkjr_std_msgs_Float64> Pub_rfkjr_17;

void slros_node_init(int argc, char** argv)
{
  ros::init(argc, argv, SLROSNodeName);
  SLROSNodePtr = new ros::NodeHandle();
}

