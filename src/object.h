#ifndef __SRC_OBJECT_H__
#define __SRC_OBJECT_H__

#include <vector>
#include "position.h"
#include "global.h"

class Object{
	public:
		Object();
	private:
		Position self;
		vector<Position> shape;
};


#endif
