/** MIT License
Copyright (c) 2017 Sudarshan Raghunathan
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*
*
*@copyright Copyright 2017 Sudarshan Raghunathan
*@file motion_node.cpp
*@author Sudarshan Raghunathan
*@brief  Ros node to read direction to move in and publish velocity to turtlebot
*/
#include <cv_bridge/cv_bridge.h>
#include <cstdlib>
#include <string>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/opencv.hpp"
#include "ros/ros.h"
#include "ros/console.h"
#include "turtlebot.hpp"//importing the turtle bot header file which contains the functions
#include "line_follower_turtlebot/pos.h"


/**
*@brief Main function that reads direction from the detect node and publishes velocity to the turtlebot at a given rate
*@param argc is the number of arguments of the main function
*@param argv is the array of arugments
*@return 0
*/
int main(int argc, char **argv) {
    // Initializing node and object
    ros::init(argc, argv, "Velocity");
    ros::NodeHandle n;
    turtlebot bot;//handle for the turtlebot
    geometry_msgs::Twist velocity;
    // Creating subscriber and publisher
    ros::Subscriber sub = n.subscribe("/direction",
        5, &turtlebot::dir_sub, &bot);
    ros::Subscriber rng4 = n.subscribe('/pi_sonar/sonar_4',10,&turtlebot::cbLeft,&bot) 
    ros::Subscriber rng3 = n.subscribe('/pi_sonar/sonar_3',10,&turtlebot::cbFront,&bot)
    ros::Subscriber rng2 = n.subscribe('/pi_sonar/sonar_2',10,&turtlebot::cbFrontRight,&bot)
    ros::Subscriber rng1 = n.subscribe('/pi_sonar/sonar_1',10,&turtlebot::cbFrontLeft,&bot) 
    ros::Subscriber rng0 = n.subscribe('/pi_sonar/sonar_0',10,&turtlebot::cbRight,&bot)    
    ros::Publisher pub = n.advertise<geometry_msgs::Twist>
        ("/cmd_vel", 10);//defines what type of messages the publisher should publish and to what topic
    ros::Rate rate(10);
    while (ros::ok()) {
        ros::spinOnce();
        // Publish velocity commands to turtlebot
        bot.vel_cmd(velocity, pub, rate);//using the function found in turtlebot
        rate.sleep();
    }
    return 0;
}