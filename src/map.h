#ifndef __SRC_MAP_H__
#define __SRC_MAP_H__

#include <vector>
#include "obstacle.h"
#include "position.h"
#include "view.h"

namespace robot {
	
class Map {
	
	public:
		void addView(View const &view){
			ViewVector.push_back(view);
		}

		typedef std::vector<View>::const_iterator const_iterator;
		
		const_iterator begin() const {return ViewVector.begin();}
		const_iterator end() const {return ViewVector.end();}

	private:
		std::vector<View> ViewVector;
		std::vector<Position> route;

};

}


#endif
