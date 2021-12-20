#ifndef ASTAR_H
#define ASTAR_H

#include <iostream>
#include <queue>
#include <vector>
#include <stack>
#include<algorithm>

using namespace std;

 int map1[101][101] = {
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0}
};

//int8_t obstacle_data[6][2]={{2,1},{2,2},{2,3},{2,4},{2,5},{2,6}};
int8_t obstacle_data[12][2];

struct coordinate{
	int x;
	int y;
};
vector<coordinate> obs_vector;

vector<coordinate> path;
typedef struct Node {
	int x,y;
	int g; //起始点到当前点实际代价
	int h;//当前节点到目标节点最佳路径的估计代价
	int f;//估计值
	Node* father;
	Node(int x,int y) {
		this->x = x;
		this->y = y ;
		this->g = 0;
		this->h = 0;
		this->f = 0;
		this->father = NULL;
	}
	Node(int x,int y,Node* father) {
		this->x = x;
		this->y = y ;
		this->g = 0;
		this->h = 0;
		this->f = 0;
		this->father = father;
	}
}Node;
 
class Astar{
public:
	Astar();
	~Astar();
	void search(Node* startPos,Node* endPos);
	void checkPoit(int x,int y,Node* father,int g);
	void NextStep(Node* currentPoint);
	int isContains(vector<Node*>* Nodelist ,int x,int y);
	void countGHF(Node* sNode,Node* eNode,int g);
	static bool compare(Node* n1,Node* n2);
	bool unWalk(int x,int y);
	void printPath(Node* current);
	void printMap();
	vector<Node*> openList;
	vector<Node*> closeList;
	Node *startPos;
	Node *endPos;
	static const int WeightW = 10;// 正方向消耗
	static const int WeightWH = 14;//打斜方向的消耗
	static const int row = 9;
	static const int col = 9;
};

#endif