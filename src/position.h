#ifndef __SRC_POSITION_H__
#define __SRC_POSITION_H__

#include <ostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include "global.h"


namespace robot {
class Angle;

/*
 * Position is designed for 3D, it could also be used in 2D if z=0,
 *
 */

class Position{
	public:
		Position(): x(0),y(0),z(0) {};
		Position(double x, double y, double z=0):x(x),y(y),z(z) {}
		/*
		 * by default and convention, there is a implict cordinates position (0,0,0) so that
		 * the value for this position is (x,y,z), 
		 *
		 * currnetly the transform method only support 2D transform.
		 * 
		 * the first parameter _cord_ is the zero podouble of the coordinates 
		 * which the position is being transformed into.
		 *
		 * the second parameter is the angle between the current y axis direction 
		 * and the y axis direction that is going to transform into.
		 *
		 * see http://www.continuummechanics.org/cm/coordxforms.html for more.
		 *
		 */
		Position const transform(Position const &cord, Angle const &ycur_ynew) const;
		
		Position operator + (Position const &pos) const { 
			return Position(X()+pos.X(),Y()+pos.Y(),Z()+pos.Z());
		}

		Position operator - (Position const &pos) const {
			return Position(X()-pos.X(),Y()-pos.Y(),Z()-pos.Z());
		}

		Position operator - () const {
			return Position(-X(),-Y(),-Z());
		}
		
		double distance (Position const &pos) const{
			return std::sqrt(std::pow(X()-pos.X(),2)+std::pow(Y()-pos.Y(),2));
		}

		//given a angle and a distance, return the position along this direction and has the given distance.
		//for 2D only
		Position directPosition(Angle const &a, double distance) const;

		std::vector<Position> toPositions() const;

		bool isInArea(std::vector<Position> const &t) const;
		
		double X() const {return x;}
		double Y() const {return y;}
		double Z() const {return z;}

		double minX() const {return x;}
		double minY() const {return y;}
		double maxX() const {return x;}
		double maxY() const {return y;}
		
		int size() const {return 1;}
	private:
		double x;
		double y;
		double z;
};

static inline std::ostream & operator <<(std::ostream &os, Position const & position){
//	os << "("<<position.X()<<","<<position.Y()<<","<<position.Z()<<") ";
	std::fixed(os);
//	os << std::setprecision(2) <<"("<<float(position.X())<<","<<float(position.Y())<<") ";
	os << std::setprecision(2) <<float(position.X())<<" "<<float(position.Y())<<" ";
	return os;
}

}
#endif

