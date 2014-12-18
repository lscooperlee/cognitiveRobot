#ifndef __SRC_ROBOT_LASERROBOT_H__
#define __SRC_ROBOT_LASERROBOT_H__

#include "robot.h"

namespace robot {

class LaserRobot: public Robot {
	public:
		static unsigned int const LASER_MAX=1000000;
};

}

#endif
