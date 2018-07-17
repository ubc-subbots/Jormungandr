/*
 * Created By: Reid Oliveira
 * Created On: March 24, 2018
 * Description: Abstract class for subroutines
 */

#include "Subroutine.h"
#include <geometry_msgs/TwistStamped.h>

Subroutine::Subroutine() {}

void Subroutine::startup() {
    ros::NodeHandle nh;
    ros::NodeHandle private_nh("~");

    subscriptions_ = getSubscriptions(nh);

    std::string topic   = private_nh.resolveName("output");
    uint32_t queue_size = 10;
    publisher_ =
    private_nh.advertise<geometry_msgs::TwistStamped>(topic, queue_size);
}

void Subroutine::shutdown() {
    publisher_.shutdown();

    for (ros::Subscriber subscription : subscriptions_) {
        subscription.shutdown();
    }
    subscriptions_.clear();
}

void Subroutine::publishCommand(nav_msgs::Odometry msg) {
    geometry_msgs::TwistStamped twistStamped;

    twistStamped.twist.linear.x = msg.twist.twist.linear.x;
    twistStamped.twist.linear.y = msg.twist.twist.linear.y;
    twistStamped.twist.linear.z = msg.twist.twist.linear.z;

    if(msg.pose.pose.position.z > 0){
        twistStamped.twist.linear.x = UP;
    }else if(msg.pose.pose.position.z > 0) {
        twistStamped.twist.linear.x = DOWN;
    }

    publisher_.publish(twistStamped);
}

geometry_msgs::Vector3 Subroutine::makeVector(double x, double y, double z) {
    geometry_msgs::Vector3 v;
    v.x = x;
    v.y = y;
    v.z = z;

    return v;
}