#ifndef __SRC_VIEW_H__
#define __SRC_VIEW_H__

#include <vector>
#include "global.h"
#include "obstacle.h"

namespace robot {


class View {
	public:
		std::vector<Obstacle> obstacles;
		View const &transform();
};

}
#endif
