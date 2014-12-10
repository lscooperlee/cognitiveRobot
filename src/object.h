#ifndef __SRC_OBJECT_H__
#define __SRC_OBJECT_H__

#include <vector>
#include "position.h"
#include "global.h"

namespace robot {


class Object{
	protected:
		Position position;
		std::vector<Position> shape;
};


}
#endif
