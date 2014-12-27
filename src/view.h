#ifndef __SRC_VIEW_H__
#define __SRC_VIEW_H__

#include <vector>
#include "global.h"
#include "angle.h"
#include "obstacle.h"

namespace robot {

class Area;

class View {

	public:
		View(){}

		View(std::initializer_list<Obstacle> oblist);

		View const transform(Position const &cord, Angle const &ycur_ynew) const;
		
		void addObstacle(Obstacle const &obstacle);
		void addObstacles(std::vector<Obstacle> const &obset);

		void putPosition(Position const &position);
		void putAngle(Angle const &angle);
		
		Position const &getPosition() const ;
		Angle const &getAngle() const ;

		typedef std::vector<Obstacle>::const_iterator const_iterator;
		
		const_iterator begin() const {return Obstacles.begin();}
		const_iterator end() const {return Obstacles.end();}

		unsigned int size() const {return Obstacles.size();}
		
		std::vector<Position> toPositions() const ;

		View extend(double distance) const ;

		//given a position and the angle in a view, cut all obstacles on the angle side of the line that goes across the position.
		View cut(Position const &pos, Angle const &ang) const;

		//
		View deleteArea(View const &view) const;
		View deleteAreaExtend(View const &view, double distance) const;

		View operator -(View const &view) const ;
		View operator +(View const &view) const ;

	private:
		std::vector<Obstacle> Obstacles;
		Position globalPosition;
		Angle facingAngle;
		
		View addNewView(Area const &area) const;
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
