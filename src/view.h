#ifndef __SRC_VIEW_H__
#define __SRC_VIEW_H__

#include <set>
#include "global.h"
#include "obstacle.h"
#include "angle.h"

namespace robot {

class View {

	public:
		View(){}

		View(std::initializer_list<Obstacle> oblist);

		View const transform(Position const &cord, Angle const &ycur_ynew) const;
		
		void addObstacle(Obstacle const &obstacle);
		void addObstacles(std::multiset<Obstacle> const &obset);

		void putPosition(Position const &position);
		void putAngle(Angle const &angle);
		
		Position const &getPosition() const ;
		Angle const &getAngle() const ;

		typedef std::multiset<Obstacle>::const_iterator const_iterator;
		
		const_iterator begin() const {return Obstacles.begin();}
		const_iterator end() const {return Obstacles.end();}

		int size() const {return Obstacles.size();}

		View operator -(View const &view) const ;
		
		std::vector<Position> toPositions() const ;

		//given a position and the angle in a view, cut all obstacles on the angle side of the line that goes across the position.
		View cut(Position const &pos, Angle const &ang) const;

		double minX() const ;
		double minY() const ;
		double maxX() const ;
		double maxY() const ;


	private:
		std::multiset<Obstacle> Obstacles;
		Position globalPosition;
		Angle facingAngle;
};

static inline std::ostream & operator <<(std::ostream &os, View const &view) {
	os << "globalPosition: "<< view.getPosition() <<" facingAngle "<<view.getAngle();

	for(View::const_iterator i=view.begin();i!=view.end();++i){
		Obstacle const &o=*i;
		os<<o<<" ";
	}
	return os;
}

}
#endif
