#ifndef __SRC_VIEW_H__
#define __SRC_VIEW_H__

#include <vector>
#include "global.h"
#include "obstacle.h"

class View {
	public:
		vector<Obstacle> obstacles;
		View const &transform();
};

#endif
