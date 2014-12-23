#ifndef __SRC_MAP_H__
#define __SRC_MAP_H__

#include <vector>
#include <set>
#include "global.h"

namespace robot {

class View;
class Position;
class Obstacle;
	
class Map {
	
	public:

		Map(){}
		Map(std::initializer_list<View> vlist);

		/*
		 * BE CAUTIOUS, THE view has to be transformed first, 
		 * add an untransformed view to a map is meaningless
		 *
		 */
		void addView(View const &view) ;
		void addViewbyCut(View const &view) ;
		void addViewbyFullCut(View const &view) ;
		void addViewbyFullDeleteArea(View const &view) ;
		void addViewbyFullDeleteAreaExtend(View const &view, double distance) ;

		std::vector<Position> toPositions() const;

		View toView() const ;

		typedef std::vector<View>::const_iterator const_iterator;
		const_iterator begin() const {return ViewVector.begin();}
		const_iterator end() const {return ViewVector.end();}

		double minX() const;
		double minY() const;
		double maxX() const;
		double maxY() const;

		unsigned int size() const {return ViewVector.size();}

	private:
		std::vector<View> ViewVector;
		std::vector<Position> route;

		std::multiset<Obstacle> toObstacles() const ;

};

}


#endif
