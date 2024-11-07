#ifndef _SLROS_INITIALIZE_H_
#define _SLROS_INITIALIZE_H_

#include "slros_busmsg_conversion.h"
#include "slros_generic.h"
#include "rfkjr_types.h"

extern ros::NodeHandle * SLROSNodePtr;
extern const std::string SLROSNodeName;

// For Block rfkjr/Subscribe
extern SimulinkSubscriber<std_msgs::Float64, SL_Bus_rfkjr_std_msgs_Float64> Sub_rfkjr_16;

// For Block rfkjr/Publish
extern SimulinkPublisher<std_msgs::Float64, SL_Bus_rfkjr_std_msgs_Float64> Pub_rfkjr_17;

void slros_node_init(int argc, char** argv);

#endif
