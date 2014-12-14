#ifndef __SRC_VIEW_H__
#define __SRC_VIEW_H__

#include <set>
#include "global.h"
#include "obstacle.h"

namespace robot {


class View {

	public:
		View(std::set<Obstacle> const &obs){obstacles=obs;}
		View(){}
		View const &transform();
		void insert(Obstacle const &obstacle){obstacles.insert(obstacle);}


	private:
		std::set<Obstacle> obstacles;
};

}
#endif
