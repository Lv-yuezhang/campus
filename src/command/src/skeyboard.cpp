#include <ros/ros.h>
#include "command/turn.h"
#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <map>

int getch(void);

std::map<char, std::vector<float>> moveBindings
{
	{'w', {1}},
	{'s', {2}},
	{'a', {3}},
	{'d', {4}},
};

float turn;
char key(' ');

int main(int argc, char** argv) {
	ros::init(argc, argv, "skeyboard");
	ros::NodeHandle n;
	ros::Publisher pub = n.advertise<command::turn>("/turn_info", 1);
	ros::Rate loop_rate(1);

	while(true){
		command::turn turn_msg;
		key = getch();
		if (moveBindings.count(key) == 1)
		{
			turn = moveBindings[key][0];
			printf("\rCurrent:%f  %c   ", turn,key);

		}
		if (key == '\x03')
		{
			break;
		}
		turn_msg.sss = turn;
		pub.publish(turn_msg);
		ros::spinOnce();
		//loop_rate.sleep();
	}
	return 0;
}

int getch(void) {
	int ch;
	struct termios oldt;
	struct termios newt;
	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	newt.c_iflag |= IGNBRK;
	newt.c_iflag &= ~(INLCR | ICRNL | IXON | IXOFF);
	newt.c_lflag &= ~(ICANON | ECHO | ECHOK | ECHOE | ECHONL | ISIG | IEXTEN);
	newt.c_cc[VMIN] = 1;
	newt.c_cc[VTIME] = 0;
	tcsetattr(fileno(stdin), TCSANOW, &newt);
	ch = getchar();
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	return ch;
}