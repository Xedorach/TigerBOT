#pragma once
#include <geometry_msgs/Twist.h>
#include <sensor_msgs/Range.h>
#include <vector>
#include "ros/ros.h"
#include "line_follower_turtlebot/pos.h"

/**
@brief Class turtlebot subscribes to the directions published and publishes velocity commands
*/
class turtlebot {
 public:
    int dir;// Direction message to read published directions
    float range4;//left side sensor
    float range3;//front sensor message
    float range2;//front right sensor message
    float range1;//front left sensor messagei
    float range0;//right side sensor
                 
/**
@brief Callback used to subscribe to the direction message published by the Line detection node
@param msg is the custom message pos which publishes a direction int between 0 and 3
@return none
*/
    void dir_sub(line_follower_turtlebot::pos msg);
    void cbLeft(sensor_msgs::Range msg);
    void cbFront(sensor_msgs::Range msg);
    void cbFrontRight(sensor_msgs::Range msg);
    void cbFrontLeft(sensor_msgs::Range msg);
    void cbRight(sensor_msgs::Range msg);
    
/**
@brief Function to publish velocity commands based on direction
@param velocity is the twist 
@param pub is used to publish the velocity commands to the turtlebot
@param rate is the ros loop rate for publishing the commands
@return none
*/    
    void vel_cmd(geometry_msgs::Twist &velocity,
     ros::Publisher &pub, ros::Rate &rate);
};
                

