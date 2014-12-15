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
		/*
		 * BE CAUTIOUS, THE view has to be transformed first, 
		 * add an untransformed view to a map is meaningless
		 *
		 */
		void addView(View const &view){
			if(ViewVector.size()==0){
				ViewVector.push_back(view);
			}else{
				View const &tv=ViewVector.back();
				View const nv=view-tv;
				ViewVector.push_back(nv);
			}
		}

		std::multiset<Obstacle> toObstacles() const {
			std::multiset<Obstacle> obstacles;
			for(const_iterator i=begin();i!=end();++i){
				View const &v=*i;
				for(View::const_iterator j=v.begin();j!=v.end();++j){
					Obstacle const &o=*j;
					obstacles.insert(o);
				}
			}
			return obstacles;
		}

		View toView() const{
			View v;
			v.addObstacles(toObstacles());
			return v;
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
