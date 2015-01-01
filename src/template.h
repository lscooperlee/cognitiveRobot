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
		std::vector<Position> vp=to_positions(p);
		v.insert(v.end(),vp.begin(),vp.end());
	}
	return v;
}
template <typename T=Position>
std::vector<Position> const to_positions(Position const &p){
	std::vector<Position> v;
	v.push_back(p);
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

template <typename T>
bool is_equal(T const &t1, T const &t2){
	
	if(t1.size()!=t2.size()){
		return false;
	}

	for(unsigned int i=0;i<t1.size();i++){
		if(!is_equal(t1[i],t2[i])){
			return false;
		}
	}

	return true;
}

template <typename T=Position>
bool is_equal(Position const &p1, Position const &p2) { 
	return p1.X()==p2.X() && p1.Y()==p2.Y() && p1.Z()==p2.Z();
}


template <typename T>
std::size_t hash(T const &t) {
	std::size_t r=0;
	for(auto const &c:t){
		r+=hash(c);
	}
	return r;
}

template <typename T=Position>
std::size_t hash(Position const &p) {
	return std::hash<double>()(p.X())+std::hash<double>()(p.Y())+std::hash<double>()(p.Z());
}


}
#endif
