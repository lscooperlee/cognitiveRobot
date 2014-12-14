#ifndef __SRC_OBSTACLE_H__
#define __SRC_OBSTACLE_H__

#include "global.h"
#include "position.h"
#include "object.h"

namespace robot {

class Obstacle: public Object {

	public:
		virtual bool operator <(Obstacle const &obstacle) const { return size() < obstacle.size(); };

		/*
		 * a string of points for any shape,
		 * the format should be in X1 Y1 X2 Y2 ... Xn Yn
		 * exceptions would be ignored
		 */
		Obstacle(std::string const &str){
			std::string::size_type pos=0;
			std::string s=str;
			double x,y;
			while(1){
				try{
					s=s.substr(pos);
					x=std::stod(s,&pos);
					s=s.substr(pos);
					y=std::stod(s,&pos);
					
					shape.push_back(Position(x,y));
				}catch(...){
					break;
				}
				
			}

			position=shape.back();
		}
		/*
		 * an obstacle needs at least two points. 
		 */
		Obstacle(Position const &p1, Position const &p2){
			shape.push_back(p1);
			shape.push_back(p2);
			position=p1;
		}
		
		Obstacle(double x1, double y1, double x2, double y2){
			shape.push_back(Position(x1,y1));
			shape.push_back(Position(x2,y2));
			position=Position(x1,y1);
		}

		Obstacle(std::vector<Position> const &obshape){shape=obshape;}

		virtual bool size() const {
			if(shape.size() < 2){
				return 0;
			}
			Position const &p1=shape[0];
			Position const &p2=shape[1];
			return p1.distance(p2);
		}

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
