#ifndef __SRC_POSITION_H__
#define __SRC_POSITION_H__

#include "global.h"
#include "angle.h"

namespace robot {


class Position{
	public:
		Position(): x(0),y(0),z(0) {};
		Position(double x, double y, double z=0):x(x),y(y),z(z) {}
		/*
		 * by default and convention, there is a implict cordinates position (0,0,0) so that
		 * the value for this position is (x,y,z), 
		 *
		 * In this system, the robot's facing direction is always the Y axis, 
		 * the second parameter is actually the angle between the two respective X,Y and Z axes.
		 * the angles between X and Y, X and Y, and Y and Z in different 
		 * coordinates can be caculated too.
		 *
		 * the first parameter _cord_ is the zero point of the coordinates 
		 * which the position is being transformed into.
		 *
		 * see http://www.continuummechanics.org/cm/coordxforms.html for more.
		 *
		 */
		Position const &transform(Position const &cord, Angle const &ang);
		

	private:
		double x;
		double y;
		double z;
};

}
#endif

