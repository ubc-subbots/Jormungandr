/*
 * Created By: Reid Oliveira
 * Created On: March 17, 2018
 * Description:
 */
#ifndef DECISION_SUBROUTINE_H
#define DECISION_SUBROUTINE_H

#include <ros/ros.h>
#include <geometry_msgs/Twist.h>

class Subroutine {
public:
    Subroutine(int argc, char **argv, std::string node_name) {
        ros::init(argc, argv, node_name);
    }

    virtual void startup() = 0;
    virtual void shutdown() = 0;
    void publishCommand(const geometry_msgs::Twist &msg) {
        publisher_.publish(msg);
    }

protected:
    ros::Publisher publisher_;
};

#endif //DECISION_SUBROUTINE_H
