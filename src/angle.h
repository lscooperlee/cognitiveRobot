#ifndef __SRC_ANGLE_H__
#define __SRC_ANGLE_H__


#include "global.h"
#include "math.h"

namespace robot {

/*
 * different system may use different angle unit.
 * Also, the range of angle may be from negative to positive or always positive.
 * the zero angle sometimes is X axis, sometimes is Y axis.
 * all these dirty work should be done by this class.
 *
 * in this system, the angle unit is radian, range is from -PI to PI. 
 * zero angle is in Y axis no matter its 2D or 3D coordinates. 
 */

class Angle {

	public:
		Angle(): angle(0) {}
		Angle(double a): angle(a) {}

		Angle operator +(Angle const &ang) const {
			double na=fixAngle(ang.getAngle() + angle);
			return Angle(na);
		}

		Angle operator -(Angle const &ang) const {
			double na=fixAngle(ang.getAngle() - angle);
			return Angle(na);
		}

		double getAngle() const {return angle;}
		double convertToRadian(double a) const { return fixAngle(a*PI/180); };

	private:
		double angle;
		double fixAngle(double oa) const{
			if (oa < -PI)
				oa = oa + 2 * PI;
			else if (oa > PI)
				oa = oa - 2 * PI;
			return oa;
		}
};

}

#endif
