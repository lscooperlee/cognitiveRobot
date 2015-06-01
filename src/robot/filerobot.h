#ifndef __SRC_ROBOT_FILEROBOT_H__
#define __SRC_ROBOT_FILEROBOT_H__

#include <fstream>
#include <unordered_map>
#include "laserrobot.h"

namespace robot {

class Display;
class View;

struct viewhash{
	std::size_t operator () (View const *v) const {
		return hash(v->getPosition())+hash(v->getAngle());
	}
};

struct viewequal{
	bool operator ()(View const *v, View const *w) const {
		return (is_equal(v->getPosition(), w->getPosition())) && (v->getAngle() == w->getAngle());
	}
};

class FileRobot: public LaserRobot {

	public:
		FileRobot(char const *filename) throw(FailCreateException);
		FileRobot(std::string const filename) throw(FailCreateException);
		FileRobot(FileRobot const &filerobot);

		~FileRobot();
		
		void setDisplay(Display *const dis) {display=dis;}
		View const look() throw(NoViewException) override;
		Map const doMap(int c=0) ;

	private:
		std::ifstream *file;
		std::string filename;

		Display *display=nullptr;

		Map const do_map_backward(int sz) const;

		std::vector<View> doTransform(int sz) const;

		bool isRevisit(View const &cur,View const &last, View const &memorycur, View const &memorylast) const;

		std::unordered_map<View const *, bool, viewhash, viewequal> getRevisitDict(std::vector<View> const &tv) const;

};

}

#endif
