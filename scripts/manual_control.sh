#!/bin/bash

# Source ROS 2 setup file
source /opt/ros/humble/setup.bash
source /home/thermalbot/ros2_ws/install/setup.sh

# Launch the ROS 2 Joy node
ros2 run joy joy_node &

# Run the manual_control script
./home/thermalbot/ros2_ws/src/thermalbot/control/manual_control
