#ifndef __SRC_VIEW_H__
#define __SRC_VIEW_H__

#include <vector>
#include <memory>
#include <unordered_set>
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
		View operator &(View const &view) const;

		std::pair<Position, Position> const makeFacingPair(View const &v) const ;

		void setHighlight(bool h) const {highlight=h;};
		bool getHighlight() const {return highlight;};

		View const doSquare() const ;
		View const addSquare() const {
			return doSquare()+*this;
		}

		void addSameSpaceView(std::initializer_list<View const *> lst) const ;

		View const *getSameSpaceView(int n) const {
			return samespace[n];
		}

		std::size_t getSameSpaceSize() const {
			return samespace.size();
		}

		View const getLocalSpace(View const &last) const ;

		//std::pair<View const, bool> merge(View const &view) const;
		View const merge(View const &view) const;

		Position const &getRevisitCheckPoint(View const *last=nullptr) const;

	private:
		std::vector<Obstacle> Obstacles;
		Position globalPosition;
		Angle facingAngle;

		mutable bool highlight=false;
		mutable std::vector<View const *> samespace;
		
		View addNewView(Area const &area) const;
};

std::ostream & operator <<(std::ostream &os, View const &view) ;

}
#endif
