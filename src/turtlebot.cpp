#include <geometry_msgs/Twist.h>
#include <sensor_msgs/Range.h>
#include <vector>
#include "ros/ros.h"
#include "ros/console.h"
#include "turtlebot.hpp"
#include "line_follower_turtlebot/pos.h"

void turtlebot::dir_sub(line_follower_turtlebot::pos msg) {
    turtlebot::dir = msg.direction;
}//call back function for the direction
void turtlebot::cbLeft(sensor_msgs::Range msg){
    turtlebot::range4 = msg.range;
}//callback function for the range of sensor left
void turtlebot::cbFront(sensor_msgs::Range msg){
    turtlebot::range3 = msg.range;
}//callback function for the range of sensor forward
void turtlebot::cbFrontRight(sensor_msgs::Range msg){
    turtlebot::range2 = msg.range;
}//callback function for sensor front right
void turtlebot::cbFrontLeft(sensor_msgs::Range msg){
    turtlebot::range1 = msg.range;
}//call back function for sensor front left
void turtlebot::cbRight(sensor_msgs::Range msg){
    turtlebot::range0=msg.range;
}//callback function for sensor on the right
int man=0;
int step=0;
int times=0;
//add call back functions for the other ranges
void turtlebot::vel_cmd(geometry_msgs::Twist &velocity,
 ros::Publisher &pub, ros::Rate &rate) {
   int index=0;
   //the robot checks for an obstacle facing it, then stops
if ((turtlebot::range3<=0.4 && turtlebot::range3>=0.02) || (turtlebot::range2<=0.4 && turtlebot::range2>=0.02) || (turtlebot::range1<=0.4 && turtlebot::range1>=0.02)&& step!=1)
        {
        ROS_INFO_STREAM("THERE IS AN OBSTACLE");
        ros::Duration(3.0).sleep();//waits 
        velocity.linear.x = 0.3;//moves forward to see if the obstacle remained there 
        velocity.angular.z = 0;
        pub.publish(velocity);
        index=0;
        man=1;  
        if ((turtlebot::range3<=0.35 && turtlebot::range3>=0.02) || (turtlebot::range2<=0.399 && turtlebot::range2>=0.02))
            {
            for (int i=0; i<=15;i++)
                {//the robot would turn 90 degrees to the left to move away from the obstacle
                velocity.linear.x=0;//the linear velocity is 0
                velocity.angular.z=1.0;//the angular velocity is 1 rad/s
                pub.publish(velocity);//the velocity is being published
                rate.sleep();
                ROS_INFO_STREAM("MANUVERing");
                }
            rate.sleep();
            //robot begins to move forward to clear the obstacle which was in front of it
            for (int i=0; i<=100;i++)
                {
                velocity.linear.x=0.1;//here linear velocity is being published for forward movement
                velocity.angular.z=0;//no angular velocity is used here so the robot only proceeds straight
                pub.publish(velocity);// the velocity is being published
                rate.sleep();
                ROS_INFO_STREAM("MOVING FORWARD TO CLEAR OBESTEKAL");
                }
            rate.sleep();
            for (int i=0; i<=15;i++)
                {//robot turns back -90 degrees to pass the obstacle
                velocity.linear.x=0;
                velocity.angular.z=-1.0;//same angular speed and same number of iterations, i.e. ensure it is 90 degrees rotation 
                pub.publish(velocity);
                rate.sleep();
                ROS_INFO_STREAM("TURNING BACK TO MOVE FORWARD");
                }
            for (int i=0; i<=105;i++)
                {//the robot moves forward to clear the obstacle
                velocity.linear.x=0.1;
                velocity.angular.z=0;
                pub.publish(velocity);
                rate.sleep();
                ROS_INFO_STREAM("GOING FORWARD TO MOVE CLEAR OBESTEKALLLLLLAK");
                }
            rate.sleep();
            for (int i=0; i<=15;i++)
                {//after the robot has cleared the obstacle, it would turn back to return to the path
                velocity.linear.x=0;
                velocity.angular.z=-1.0;
                pub.publish(velocity);
                rate.sleep();
                ROS_INFO_STREAM("TURNING BACK TO MOVE FORWARD");
                }
            rate.sleep();
                //moving forward to the track
            for (int i=0; i<=75;i++)
                {//the robot returns back onto the track 
                velocity.linear.x=0.1;
                velocity.angular.z=0;
                pub.publish(velocity);
                rate.sleep();
                ROS_INFO_STREAM("GOING BACK TO THE TREK");
                }
            rate.sleep();
            //the robot rotates a little to ensure it doesn't stray off the track
            for (int i=0; i<=10;i++){
                velocity.linear.x=0;
                velocity.angular.z=1.0;
                pub.publish(velocity);
                rate.sleep();
                ROS_INFO_STREAM("GOING BACK ON THE RIGHT BATH");
                }

            }
            //in the case there is an obstacle which was to the left of the robot it would go to the right
            else if ((turtlebot::range1<=0.399 && turtlebot::range1>=0.02))
            {
            for (int i=0; i<=15;i++)
                {//the robot would turn -90 degrees to the right to move away from the obstacle
                velocity.linear.x=0;//the linear velocity is 0
                velocity.angular.z=-1.0;//the angular velocity is 1 rad/s
                pub.publish(velocity);//the velocity is being published
                rate.sleep();
                ROS_INFO_STREAM("MANUVERing");
                }
            rate.sleep();
            //robot begins to move forward to clear the obstacle which was to its left
            for (int i=0; i<=100;i++)
                {
                velocity.linear.x=0.1;//here linear velocity is being published for forward movement
                velocity.angular.z=0;//no angular velocity is used here so the robot only proceeds straight
                pub.publish(velocity);// the velocity is being published
                rate.sleep();
                ROS_INFO_STREAM("MOVING FORWARD TO CLEAR OBESTEKAL");
                }
            rate.sleep();
            for (int i=0; i<=15;i++)
                {//robot turns back 90 degrees to pass the obstacle
                velocity.linear.x=0;
                velocity.angular.z=1.0;//same angular speed and same number of iterations, i.e. ensure it is 90 degrees rotation 
                pub.publish(velocity);
                rate.sleep();
                ROS_INFO_STREAM("TURNING BACK TO MOVE FORWARD");
                }
            for (int i=0; i<=105;i++)
                {//the robot moves forward to clear the obstacle
                velocity.linear.x=0.1;
                velocity.angular.z=0;
                pub.publish(velocity);
                rate.sleep();
                ROS_INFO_STREAM("GOING FORWARD TO MOVE CLEAR OBESTEKALLLLLLAK");
                }
            rate.sleep();
            for (int i=0; i<=15;i++)
                {//after the robot has cleared the obstacle, it would turn back to return to the path
                velocity.linear.x=0;
                velocity.angular.z=1.0;
                pub.publish(velocity);
                rate.sleep();
                ROS_INFO_STREAM("TURNING BACK TO MOVE FORWARD");
                }
            rate.sleep();
                //moving forward to the track
            for (int i=0; i<=75;i++)
                {//the robot returns back onto the track 
                velocity.linear.x=0.1;
                velocity.angular.z=0;
                pub.publish(velocity);
                rate.sleep();
                ROS_INFO_STREAM("GOING BACK TO THE TREK");
                }
            rate.sleep();
            //the robot rotates a little to ensure it doesn't stray off the track
            for (int i=0; i<=10;i++){
                velocity.linear.x=0;
                velocity.angular.z=-1.0;
                pub.publish(velocity);
                rate.sleep();
                ROS_INFO_STREAM("GOING BACK ON THE RIGHT BATH");
                }

            }
               
            //once the turtlebot has finished rotating the 90 degrees it begins to move forward until it has cleared the object infront of it

                man=0;
                ROS_INFO_STREAM("FINISHED MANUVEERING");
        //else in the case of both the right and the left being blocked, i.e. not the forward path, the robot would simply proceed forward
        else{
            for (int i=0; i<=75;i++)
                {//the robot moves forward 
                velocity.linear.x=0.1;
                velocity.angular.z=0;
                pub.publish(velocity);
                rate.sleep();
                ROS_INFO_STREAM("GOING BACK TO THE TREK");
                }
            rate.sleep();
        }
        }

else{
    if (turtlebot::dir == 0) {
        velocity.linear.x = 0.1;
        velocity.angular.z = 0.15;
        pub.publish(velocity);
        index=1;
        rate.sleep();
        ROS_INFO_STREAM("Turning Left");
    }
    // If direction is straight
    if (turtlebot::dir == 1) {
        velocity.linear.x = 0.15;
        velocity.angular.z = 0;
        pub.publish(velocity);
        rate.sleep();
        index=0;
        ROS_INFO_STREAM("Straight");
    }
    // If direction is right
    if (turtlebot::dir == 2) {
        velocity.linear.x = 0.1;
        velocity.angular.z = -0.15;
        pub.publish(velocity);
        index=2;
        rate.sleep();
        ROS_INFO_STREAM("Turning Right");
    }

    // If robot has to search
    if (turtlebot::dir == 3 && index == 2){
        velocity.linear.x = 0;
        velocity.angular.z = -0.15;
        pub.publish(velocity);
        rate.sleep();
        ROS_INFO_STREAM("Searching");
    }
    //if the robot has to search in the left 
    if (turtlebot::dir == 3 && index==1) {
        velocity.linear.x = 0;
        velocity.angular.z = 0.15;
        pub.publish(velocity);
        rate.sleep();
        ROS_INFO_STREAM("Searching");
    }
    if (turtlebot::dir == 3 && index==0) {
        velocity.linear.x = 0;
        velocity.angular.z = -0.15;
        pub.publish(velocity);
        rate.sleep();
        ROS_INFO_STREAM("Searching");
    }
    }

}