#ifndef __SRC_ROBOT_FILEROBOT_H__
#define __SRC_ROBOT_FILEROBOT_H__

#include "laserrobot.h"

using namespace robot;

class FileRobot: public LaserRobot {
	public:
		FileRobot(char const *filename);
		View const &look();
};

#endif
