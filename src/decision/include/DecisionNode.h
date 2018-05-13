/*
 * Created By: Reid Oliveira
 * Created On: March 17, 2018
 * Description:
 */
#ifndef DECISION_DECISION_H_H
#define DECISION_DECISION_H_H

#include "Subroutine.h"
#include <geometry_msgs/Twist.h>
#include <ros/ros.h>
#include <unordered_map>

// state msg
#include <worldstate/state_msg.h>
// subroutines
#include "LineUpWithGate.h"
#include "LocateGate.h"

typedef int8_t state_t;

class DecisionNode {
  public:
    DecisionNode(int argc, char** argv, std::string node_name);

  private:
    std::unordered_map<state_t, Subroutine*> subroutines_;
    Subroutine* running_;
    ros::Subscriber subscriber_;

    void subscriberCallback(const worldstate::state_msg::ConstPtr& msg);
    void setupSubroutineMap(int argc, char** argv);
};
#endif // DECISION_DECISION_H_H