/*
 * Created By: Reid Oliveira
 * Created On: November 11th, 2017
 * Description:
 */

#include <HSVFilter.h>

int main(int argc, char** argv) {
    // Setup your ROS node
    std::string node_name = "filter";

    // Create an instance of your class
    HSVFilter filter(argc, argv, node_name);

    // Start up ros. This will continue to run until the node is killed
    ros::spin();

    // Once the node stops, return 0
    return 0;
}