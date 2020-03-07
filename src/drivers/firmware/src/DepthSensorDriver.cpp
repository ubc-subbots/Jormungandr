/*
 * Created By: Logan Fillo
 * Created On: October 25 2019
 * Description: Depth sensor driver
 */

#include "../include/DepthSensorDriver.h"

namespace arduino_drivers
{
    DepthSensorDriver::DepthSensorDriver() {}
    DepthSensorDriver::~DepthSensorDriver() {}

    void DepthSensorDriver::init() 
    {   
        while (!sensor.init()) 
        {   
            delay(5000);
        }

        sensor.setModel(MS5837::MS5837_30BA);
        sensor.setFluidDensity(997); // kg/m^3 (freshwater, 1029 for seawater)

    }
    void DepthSensorDriver::update(controls::ArduinoDriversMsg* output_msg, const controls::ArduinoDriversMsg* input_msg) 
    {
        // Read the latest sensor value
        sensor.read();

        // Add the latest depth to teh drivers output message
        output_msg->depth_sensor.depth = sensor.depth();
    }
    
} // namespace robot_driver