#ifndef __SRC_ANGLE_H__
#define __SRC_ANGLE_H__

#include "global.h"

class Angle {

	public:
		Angle(): angle(0) {}
		Angle(double a): angle(a) {}
		Angle operator +(Angle const &angle) const;
		double getAngle() const {return angle;}
	private:
		double angle;
};

#endif
