#ifndef __SRC_TEMPLATE_H__
#define __SRC_TEMPLATE_H__

#include <limits>
#include "area.h"

namespace robot {

class Position;
class Area;

template <typename T>
double min_x(T const &t){
	double min = std::numeric_limits<double>::max();
	
	for(auto const &c:t){
		double tmp = min_x(c);
		min = tmp < min ? tmp : min;
	}	
	return min;
}

template<typename T=Position>
double min_x(Position const &p){
	return p.X();
}

template <typename T>
double max_x(T const &t){
	double max = std::numeric_limits<double>::min();

	for(auto const &c:t){
		double tmp = max_x(c);
		max = tmp > max ? tmp : max;
	}	
	return max;
}

template<typename T=Position>
double max_x(Position const &p){
	return p.X();
}

template <typename T>
double min_y(T const &t){
	double min = std::numeric_limits<double>::max();

	for(auto const &c:t){
		double tmp = min_y(c);
		min = tmp < min ? tmp : min;
	}	
	return min;
}

template<typename T=Position>
double min_y(Position const &p){
	return p.Y();
}

template <typename T>
double max_y(T const &t){
	double max = std::numeric_limits<double>::min();

	for(auto const &c:t){
		double tmp = max_y(c);
		max = tmp > max ? tmp : max;
	}	
	return max;
}

template<typename T=Position>
double max_y(Position const &p){
	return p.Y();
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
		if(is_overlap_area(c,u)){
			return true;
		}
	}
	return false;
}
template <typename T=Position>
bool is_overlap_area(Position const &p, Area const &u){
	return p.isOverlapArea(u);
}

template <typename T>
bool is_in_area(T const &t, Area const &u){
	for(auto const &c:t){
		if(is_in_area(c,u)){
			return false;
		}
	}
	return true;
}
template <typename T=Position>
bool is_in_area(Position const &p, Area const &u){
	return p.isInArea(u);
}

template <typename T>
size_t size(T const &t){
	return t.size();
}

}

#endif
