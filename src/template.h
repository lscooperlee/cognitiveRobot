#ifndef __SRC_TEMPLATE_H__
#define __SRC_TEMPLATE_H__

#include <float.h>

namespace robot {

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

}

#endif
