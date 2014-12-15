#ifndef __SRC_MAP_H__
#define __SRC_MAP_H__

#include <vector>
#include <set>
#include "obstacle.h"
#include "position.h"
#include "view.h"

namespace robot {
	
class Map {
	
	public:
		void addView(View const &view){
			Obstacles.insert(view.begin(),view.end());
		}

		typedef std::multiset<Obstacle>::const_iterator const_iterator;
		
		const_iterator begin() const {return Obstacles.begin();}
		const_iterator end() const {return Obstacles.end();}

	private:
		std::multiset<Obstacle> Obstacles;
		std::vector<Position> route;

};

}


#endif
