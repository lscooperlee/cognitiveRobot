#ifndef __SRC_TEMPLATE_H__
#define __SRC_TEMPLATE_H__

#include <float.h>
#include "area.h"

namespace robot {

class Position;
class Area;

template <typename T>
double min_x(T const &t){
	double min = DBL_MAX;

	for(auto const &c:t){
		double tmp = c.minX();
		min = tmp < min ? tmp : min;
	}	
	return min;
}

template <typename T>
double max_x(T const &t){
	double max = -DBL_MAX;

	for(auto const &c:t){
		double tmp = c.maxX();
		max = tmp > max ? tmp : max;
	}	
	return max;
}

template <typename T>
double min_y(T const &t){
	double min = DBL_MAX;

	for(auto const &c:t){
		double tmp = c.minY();
		min = tmp < min ? tmp : min;
	}	
	return min;
}

template <typename T>
double max_y(T const &t){
	double max = -DBL_MAX;

	for(auto const &c:t){
		double tmp = c.maxY();
		max = tmp > max ? tmp : max;
	}	
	return max;
}

template <typename T>
std::vector<Position> const to_positions(T const &t){
	std::vector<Position> v;
	for(auto const &p:t){
		std::vector<Position> vp=p.toPositions();
		v.insert(v.end(),vp.begin(),vp.end());
	}
	return v;
}

template <typename T>
bool is_overlap_area(T const &t, Area const &u){
	for(auto const &c:t){
		if(c.isOverlapArea(u)){
			return true;
		}
	}
	return false;
}

template <typename T>
bool is_in_area(T const &t, Area const &u){
	for(auto const &c:t){
		if(!c.isInArea(u)){
			return false;
		}
	}
	return true;
}

}

#endif
