#ifndef __SRC_ANGLE_H__
#define __SRC_ANGLE_H__

#include <cmath>
#include <ostream>
#include <iomanip>
#include "global.h"
#include "position.h"


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

		Angle(Position const &p1, Position const &p2){
			double d=p1.distance(p2);
			double dx=p2.X()-p1.X();
			angle=std::asin(dx/d);

			if (p2.Y()<p1.Y()&&dx<0){
				angle-=PI/2;
			}else if(p2.Y()<p1.Y()&&dx>0){
				angle+=PI/2;
			}
			angle=fixAngle(angle);
		}

		Angle operator +(Angle const &ang) const {
			double na=fixAngle(ang.value() + angle);
			return Angle(na);
		}
		Angle operator +(double ang) const {
			double na=fixAngle(ang + angle);
			return Angle(na);
		}

		Angle operator -(Angle const &ang) const {
			double na=fixAngle(angle - ang.value());
			return Angle(na);
		}
		Angle operator -(double ang) const {
			double na=fixAngle(angle - ang);
			return Angle(na);
		}
		Angle operator -() const {
			double na=fixAngle(-angle);
			return Angle(na);
		}

		operator double() const {return value();}

		double cos() const {return std::cos(angle);}

		double value() const {return angle;}
		double convertToRadian(double a) const { return fixAngle(a*PI/180); }

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

static inline Angle operator +(double const ang, Angle const &angle) {
	return angle+ang;
}

static inline Angle operator -(double const ang, Angle const &angle) {
	return -angle+ang;
}

static inline std::ostream & operator<<(std::ostream &os, Angle const &angle){ 
	std::fixed(os);
	os <<std::setprecision(2)<<" <"<<angle.value() << "> ";
	return os;
}


}

#endif
