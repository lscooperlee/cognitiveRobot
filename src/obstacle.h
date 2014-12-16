#ifndef __SRC_OBSTACLE_H__
#define __SRC_OBSTACLE_H__

#include "global.h"
#include "position.h"
#include "object.h"

namespace robot {

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
		
		virtual bool size() const;

//		Obstacle(std::vector<Position> const &obshape){shape=obshape;}
		void addPosition(Position const &position);

		virtual bool operator <(Obstacle const &obstacle) const;

		template< typename T >
		bool isInArea(T const &t) const{
			for (Obstacle::const_iterator i = shape.begin(); i != shape.end(); ++i) {
				Position const &o = *i;
				if (o.isInArea(t)) {
					return true;
				}
			}
			return false;
		}
		
		Obstacle const transform(Position const &cord, Angle const &ycur_ynew) const;

		//
		//FIXME:template
		double minX() const;
		double minY() const;
		double maxX() const;
		double maxY() const;

};

static inline std::ostream & operator <<(std::ostream &os, Obstacle const &obstacle){
	os << "[ ";
	for(Obstacle::const_iterator i=obstacle.begin();i!=obstacle.end();++i){
		Position const &o=*i;
		os << o;
	}
	os << "] ";
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
