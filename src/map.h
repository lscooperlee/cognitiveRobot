#ifndef __SRC_MAP_H__
#define __SRC_MAP_H__

#include <vector>
#include <set>
#include "obstacle.h"
#include "position.h"
#include "view.h"

namespace robot {
	
class Map {

	private:
		std::set<Obstacle> Obstacles;
		std::vector<Position> route;

};

}


#endif
