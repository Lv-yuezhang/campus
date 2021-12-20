#include <iostream>
#include <ros/ros.h>
#include <std_msgs/Int8MultiArray.h>
#include <vector>

using namespace std;

int main(int argc, char **argv)
{
    ros::init(argc,argv,"obstacleTalker");
    //节点名称obstacleTalker

    ros::NodeHandle n;
    ros::Publisher obstacle_pub=n.advertise<std_msgs::Int8MultiArray>("obstacle",1000);
    //话题名称obstacle

    ros::Rate loop_rate(100);
    int8_t obstacle_data[][2]={{1,4},{1,8},
		              {2,2},{2,4},{2,6},
  		              {3,6},{3,8},
		              {4,2},{4,4},{4,6},
		              {5,2},{5,6},{5,8},{5,9},
		              {6,4},{6,5},{6,9},
		              {7,2},{7,5},{7,7},
		              {8,5},
		              {9,2},{9,3},{9,7},{9,8},
		              {10,5}};
    //存放障碍块信息的二维数组，第二个维度的内容代表障碍块的行与列，如{2,1}代表障碍块在第二行第一列的格子上

    while (ros::ok())
    {
        std_msgs::Int8MultiArray obstacle_msg;
        for(int i=0;i<sizeof(obstacle_data)/sizeof(obstacle_data[0]);i++){
            vector<int8_t> temp;
            temp.push_back(obstacle_data[i][0]);
            temp.push_back(obstacle_data[i][1]);
            obstacle_msg.data=temp;
            
            obstacle_pub.publish(obstacle_msg);
            //发布者每次会发布一个障碍块信息，按顺序依次发布。
            
            loop_rate.sleep();
        }
    }
    return 0;
}
