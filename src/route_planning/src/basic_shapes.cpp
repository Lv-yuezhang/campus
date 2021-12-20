#include <iostream>
#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <cmath>
#include <std_msgs/Int8MultiArray.h>
#include "Astar.h"
using namespace std;

#define number  3
int max_obs_size = 99;
int show_once = 0;
struct coordinate num1;
void subCallback(const std_msgs::Int8MultiArray::ConstPtr &msg) {
	if(obs_vector.size() < max_obs_size) {
		num1.x = msg->data[0];
		num1.y = msg->data[1];
		obs_vector.push_back(num1);
	}
}

int main( int argc, char** argv ) {
	ros::init(argc, argv, "points_and_lines");
	ros::NodeHandle n;
	ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 100);
	ros::Subscriber obs_sub = n.subscribe("/obstacle" , 1000 , subCallback);
	ros::Rate r(10);                //设置周期休眠时间
	visualization_msgs::Marker white,black, obs , route;        //定义黑色和白色的块
	white.header.frame_id = black.header.frame_id = obs.header.frame_id = route.header.frame_id = "/odom";
	white.header.stamp = black.header.stamp = obs.header.stamp =  route.header.stamp = ros::Time::now();
	white.ns = black.ns = obs.ns = route.ns = "points_and_lines";
	white.action = black.action = obs.action = route.action = visualization_msgs::Marker::ADD;
	white.id = 0; black.id = 1;obs.id = 2;route.id = 3;
	white.type = black.type = obs.type = route.type = visualization_msgs::Marker::POINTS;

	white.scale.x = 0.2; white.scale.y = 0.2; white.scale.z = 0;
	black.scale.x = 0.2; black.scale.y = 0.2; black.scale.z = 0;
	obs.scale.x = 0.2; obs.scale.y = 0.2; obs.scale.z = 0;
	route.scale.x = 0.2; route.scale.y = 0.2; route.scale.z = 0;

	white.color.g = 1; white.color.a = 1.0;white.color.b = 1;white.color.r = 1;
	black.color.g = 0; black.color.a = 1;black.color.b = 0;black.color.r = 0;
	obs.color.g = 0; obs.color.a = 1;obs.color.b = 0;obs.color.r = 1;
	route.color.g = 0.8; route.color.a = 1;route.color.b = 0.2;route.color.r = 0.6;

	//画棋盘格
	for(int i = -4; i < 6; i++) {
		for(int j = -4 ; j < 6; j++) {
			geometry_msgs::Point sp;
			if((i + j)%2 == 0) {
				sp.x = (i - 0.5) * 0.2;
				sp.y = (j - 0.5) * 0.2;
				white.points.push_back(sp);
			}
			else {
				sp.x = (i - 0.5) * 0.2;
				sp.y = (j - 0.5) * 0.2;
				black.points.push_back(sp);
			}
		}
	}
	while ( ros::ok() ) {
		if(obs_vector.size() >= max_obs_size - 1) {
			if(number == 1) {
			/*第一轮*/
				Astar astar1;
				Node *startPos1 = new Node(0,0);
				Node *endPos1 = new Node(9,9);
				astar1.search(startPos1,endPos1);
			}
			if(number == 2) {
			/*第二轮*/
				Astar astar1;
				Node *startPos1 = new Node(0,0);
				Node *endPos1 = new Node(5,4);
				astar1.search(startPos1,endPos1);

				Astar astar2;
				Node *startPos2 = new Node(5,4);
				Node *endPos2 = new Node(5,5);
				astar2.search(startPos2,endPos2);
			}
			if(number == 3) {
			/*第三轮*/
				Astar astar1;
				Node *startPos1 = new Node(0,0);
				Node *endPos1 = new Node(2,6);
				astar1.search(startPos1,endPos1);

				Astar astar2;
				Node *startPos2 = new Node(2,6);
				Node *endPos2 = new Node(4,2);
				astar2.search(startPos2,endPos2);

				Astar astar3;
				Node *startPos3 = new Node(4,2);
				Node *endPos3 = new Node(7,7);
				astar3.search(startPos3,endPos3);
			}
			if(show_once == 0) {
				for(vector<coordinate>::iterator it = path.begin(); it != path.end(); it++) {
					geometry_msgs::Point sp;
					sp.x = ( it ->x - 4.5) * 0.2;
					sp.y = -( -it ->y + 4.5) * 0.2;
					route.points.push_back(sp);
				}
				show_once = 1;
			}
			for(vector<coordinate>::iterator it  = obs_vector.begin(); it != obs_vector.end(); it++) {
				geometry_msgs::Point sp;
				sp.x = (it->x - 5.5) * 0.2;
				sp.y =  (it->y - 5.5)* 0.2;
				obs.points.push_back(sp);
			}
			marker_pub.publish(white);
			marker_pub.publish(black);
			marker_pub.publish(obs);
			marker_pub.publish(route);
		}
		r.sleep();
		ros::spinOnce();
	}
	return 0;
}
