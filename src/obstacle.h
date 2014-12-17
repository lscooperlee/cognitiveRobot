#ifndef __SRC_OBSTACLE_H__
#define __SRC_OBSTACLE_H__

#include "global.h"
#include "object.h"

namespace robot {

class Position;

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
		int size() const {return shape.size();}

		void addPosition(Position const &position);

		virtual bool operator <(Obstacle const &obstacle) const;

		bool isInArea(std::vector<Position> const &t) const;
		
		Obstacle const transform(Position const &cord, Angle const &ycur_ynew) const;

		double minX() const;
		double minY() const;
		double maxX() const;
		double maxY() const;

};

static inline std::ostream & operator <<(std::ostream &os, Obstacle const &obstacle){
	for(auto const &o:obstacle){
		os << o;
	}
	return os;
}

#if 0
class Obstacle2D: public Obstacle {

	public:
		/*
		 * an obstacle needs at least two points. 
		 */
		Obstacle2D(Position const &p1, Position const &p2){
			shape.push_back(p1);
			shape.push_back(p2);
			position=p1;
		}
		
		Obstacle2D(double x1, double y1, double x2, double y2){
			shape.push_back(Position(x1,y1));
			shape.push_back(Position(x2,y2));
			position=Position(x1,y1);
		}

};
#endif
}

#endif
