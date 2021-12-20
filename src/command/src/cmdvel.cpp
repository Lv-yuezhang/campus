#include <iostream>
#include <geometry_msgs/Twist.h>
#include <ros/ros.h>
#include <ros/console.h>
#include<unistd.h>
#include "command/turn.h"
#include "nav_msgs/Odometry.h"
#include "std_msgs/String.h"
#include <sensor_msgs/LaserScan.h>

using namespace std;

int turn_dir;
void turnIofoCallback(const command::turn& msg) {
	turn_dir = msg.sss;
	//cout << turn_dir << endl;
}

float x,y,z;
void callback_odom(const nav_msgs::Odometry::ConstPtr &odom) {
	x = odom -> pose.pose.position.x;
	y = odom -> pose.pose.position.y;
}

int once = 1;
vector<float> ranges;
void laserCallback(const sensor_msgs::LaserScan::ConstPtr& msg)
{
	ranges=msg->ranges;
}

int main(int argc, char **argv) {
	ros::init(argc, argv, "cmdvel");
	ros::NodeHandle n;
	ros::Publisher cmdpub= n.advertise<geometry_msgs::Twist>("/cmd_vel", 1, true);
	ros::Subscriber turn_info_sub = n.subscribe("/turn_info", 1 ,turnIofoCallback);
	ros::Subscriber odom_sub = n.subscribe("odom", 100 , callback_odom);
	ros::Subscriber sub = n.subscribe("/scan", 1, laserCallback);
	ros::Rate r(1);
	geometry_msgs::Twist twist;
	geometry_msgs::Vector3 linear;
	
	while(1) {
                if(turn_dir == 1) {
                        if(x > -0.02) {
                                linear.x = -0.3;
                        }
                        if(x < -1.75)
                                linear.x = 0.3;
                }
		if(turn_dir == 3 || turn_dir == 4) {
			linear.x = 0;
			if(once == 1) {
				once = 0;
				cout << "坐标：(" << 11 - int (ranges[180] / 0.2 + 1) << ","<< "1)"<< endl;
			}
		}
		linear.y = 0;
		linear.z = 0;
		geometry_msgs::Vector3 angular;
		angular.x = 0; angular.y = 0; angular.z = 0;
		twist.linear = linear;
		twist.angular = angular;
                cmdpub.publish(twist);
	 	ros::spinOnce();
	}
	return 0;
}