#ifndef __SRC_ROBOT_FILEROBOT_H__
#define __SRC_ROBOT_FILEROBOT_H__

#include <fstream>
#include "laserrobot.h"

namespace robot {

class FileRobot: public LaserRobot {

	public:
		FileRobot(char const *filename) throw(FailCreateException);
		FileRobot(FileRobot const &filerobot);
		~FileRobot();
		View const look() throw(NoViewException);
		Map const doMap() const;

	private:
		std::ifstream *file;
		std::string filename;
};

}

#endif
