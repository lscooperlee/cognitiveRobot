#ifndef __SRC_AREA_H__
#define __SRC_AREA_H__

#include <vector>
#include <set>
#include "global.h"

namespace robot {

class Position;

class Area {
	public:
		Area(){}
		Area(std::initializer_list<Position> &poslist){

			for(auto const &p:poslist){
				points.push_back(p);
			}

		}
	private:
		std::vector<Position> points;
};

}

#endif
