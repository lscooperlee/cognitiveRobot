#ifndef __SRC_ROBOT_FILEROBOT_H__
#define __SRC_ROBOT_FILEROBOT_H__

#include <fstream>
#include "laserrobot.h"

namespace robot {

class FileRobot: public LaserRobot {

	public:
		FileRobot(char const *filename) throw(FailCreateException);
		FileRobot(std::string const filename) throw(FailCreateException);
		FileRobot(FileRobot const &filerobot);

		~FileRobot();
		View const look() throw(NoViewException);
		Map const doMap(int c) const;

	private:
		std::ifstream *file;
		std::string filename;

		Map const do_map_forward(int c) const;
		Map const do_map_backward(int c) const;

};

}

#endif
