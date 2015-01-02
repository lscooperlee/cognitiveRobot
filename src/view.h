#ifndef __SRC_VIEW_H__
#define __SRC_VIEW_H__

#include <vector>
#include "global.h"
#include "angle.h"
#include "obstacle.h"
#include "template.h"

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

		View deleteArea(View const &view) const;
		View deleteAreaExtend(View const &view, double distance) const;

		Obstacle const & operator [] (unsigned int i) const {return Obstacles[i];}
		View operator -(View const &view) const ;
		View operator +(View const &view) const ;
		bool operator ==(View const &view) const;

		std::pair<Position, Position> const makeFacingPair(View const &v) const ;

		void setHighlight(bool h) {highlight=h;};
		bool getHighlight() const {return highlight;};

		View const doSquare() const ;
		View const addSquare() const {
			return doSquare()+*this;
		}

	private:
		std::vector<Obstacle> Obstacles;
		Position globalPosition;
		Angle facingAngle;

		bool highlight=false;
		
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
