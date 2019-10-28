/*
 * Created By: Logan Fillo
 * Created On: October 19 2019
 * Description: Thruster array controller
 */

#include <controllers/thruster_array_controller.h>

namespace thruster_controllers {

    ThrusterArrayController::ThrusterArrayController() {}

    ThrusterArrayController::~ThrusterArrayController() {}

    bool ThrusterArrayController::init(hardware_interface::ThrusterArrayInterface *robot, 
        ros::NodeHandle &root_nh, ros::NodeHandle &controller_nh)
    {   
        if (!controller_nh.getParam("names", thruster_names_))
        {
            ROS_ERROR("Couldn't retrieve thruster array name param");
            return false;
        }

        thruster_array_handle_ = robot->getHandle("thruster_array");

        if (!pid_controller_.init(ros::NodeHandle(controller_nh, "pid")))
        {
            ROS_ERROR("Could not init PID controller for thruster array");
            return false;
        }

        std::map<std::string,std::string> topics;  
        if (!controller_nh.getParam("topics", topics))
        {
            ROS_ERROR("Couldn't retrieve thruster array topics");
            return false;
        }

        decision_sub_ = root_nh.subscribe<nav_msgs::Odometry>(
            topics["decision"], msg_queue_, 
            &ThrusterArrayController::decisionCB, this);

        ROS_INFO("Thruster Array Controller Initialized");
        return true;
    }

    void ThrusterArrayController::update(const ros::Time& time, const ros::Duration& period) 
    {   
        // Get latest decision command
        decision_cmd_struct_ = *( decision_cmd_.readFromRT() );

        // // Get the desired thruster commands based on latest decision command recieved and sensor states
        // ThrusterArrayData desired_commands = calculateDesiredCommands();

        // // Calculate error for each thrusters command
        // ThrusterArrayData command_errors = calculateCommandErrors( desired_commands );

        // // Use PID controllers to get actual commands for thruster array
        // ThrusterArrayData actual_commands = calculateActualCommands( command_errors, period );

        // // Send the actual commands to the handle to be used in the hardware interface
        // thruster_array_handle_.commandThrusterArray( actual_commands );

        // ROS_INFO("Multi Thruster Controller Updated");
    }

    void ThrusterArrayController::starting(const ros::Time& time) 
    {
        // TODO: Initialize decision command struct
        decision_cmd_.initRT(decision_cmd_struct_);

        pid_controller_.reset();
    }

    void ThrusterArrayController::stopping(const ros::Time& time) 
    {
        decision_sub_.shutdown();
    }

    void ThrusterArrayController::decisionCB(const nav_msgs::Odometry::ConstPtr& msg) 
    {   
        // ROS_INFO("Got decision message");
        DecisionCmd cmd;
        // TODO: fill cmd with msg
        decision_cmd_struct_ = cmd;
        decision_cmd_.writeFromNonRT(decision_cmd_struct_);
    }

} // namespace thruster_controllers

PLUGINLIB_EXPORT_CLASS(thruster_controllers::ThrusterArrayController, controller_interface::ControllerBase)


