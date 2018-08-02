/*
 * Created By: Joel Ahn
 * Created On: March 5th, 2018
 * Description: Checks the incoming data from detection nodes
 *              and tracks the individual goals of the robot
 */

#ifndef JORMUNGANDR_WORLDSTATENODE_H
#define JORMUNGANDR_WORLDSTATENODE_H

#include "routines/Gate/AlignWithGate.h"
#include "routines/Gate/ApproachGate.h"
#include "routines/Gate/LocatingGate.h"
#include "routines/Gate/PassGate.h"
#include <ros/ros.h>
#include <unordered_map>

/* ROS msg types */
#include "routines/State.h"
#include <std_msgs/builtin_int8.h>
#include <worldstate/StateMsg.h>

typedef int8_t state_t;

class WorldStateNode {
  public:
    WorldStateNode(int argc, char** argv, std::string node_name);

  private:
    std::unordered_map<std::string, double> constants_;
    const uint8_t initial_state_ = worldstate::StateMsg::adjustingDepth;
    ros::Subscriber world_state_listener_;
    State* current_state_;
    std::unordered_map<state_t, State*> state_machine_;

    /**
     * Callback function for when data is received from gate detection node
     *
     * @param gate detection node discretized messages
     */
    void stateChangeCallBack(const worldstate::StateMsg::ConstPtr& msg);

    /**
     * Instantiate each of the individual routine nodes in ros shutdown mode
     */
    void initializeFiniteStateMachine();
    void getConstants(ros::NodeHandle nh);
};

#endif // JORMUNGANDR_WORLDSTATENODE_H
