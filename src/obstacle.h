#ifndef __SRC_OBSTACLE_H__
#define __SRC_OBSTACLE_H__

#include "global.h"
#include "object.h"

namespace robot {

class Position;
class Area;

class Obstacle: public Object {

	public:

		Obstacle();
		Obstacle(std::initializer_list<Position> &plist);

		/*
		 * a string of points for any shape,
		 * the format should be in X1 Y1 X2 Y2 ... Xn Yn
		 * exceptions would be ignored
		 */
		Obstacle(std::string const &str);
		
		/*
		 * an obstacle needs at least two points. these methods are for 2D
		 */
		Obstacle(Position const &p1, Position const &p2);
		
		Obstacle(double x1, double y1, double x2, double y2);

		double length() const;
		unsigned int size() const {return shape.size();}

		void addPosition(Position const &position);

		virtual bool operator <(Obstacle const &obstacle) const;

		Obstacle const transform(Position const &cord, Angle const &ycur_ynew) const;

		Area toArea() const;
		
		bool isSameObstacle(Obstacle const &o) const;

		Angle const getAngle() const ;
};

std::ostream & operator <<(std::ostream &os, Obstacle const &obstacle);

}
#endif
