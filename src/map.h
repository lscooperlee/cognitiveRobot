#ifndef __SRC_MAP_H__
#define __SRC_MAP_H__

#include <vector>
#include <unordered_map>
#include "global.h"
#include "position.h"
#include "view.h"

namespace robot {

class View;
class Obstacle;
class Display;
	
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
		std::vector<Map> addViewbyDeleteAreaExtend(View const &view, double distance);
		std::vector<Map> addViewbyFullDeleteAreaExtend(View const &view, double distance);

		typedef std::vector<View>::const_iterator const_iterator;
		const_iterator begin() const {return ViewVector.begin();}
		const_iterator end() const {return ViewVector.end();}

		unsigned int size() const {return ViewVector.size();}

		View const * getRevisitStartView(View const &view) const ;
		View const * getRevisitEndView(View const &view) const ;

		View const & operator [] (unsigned int i) {return ViewVector[i];}

		std::pair < Position, Position > const &getRouteItem(View const &view) const {
			std::pair<Position, Position> const &p=route.at(view);
			return p;
		}

	private:
		std::vector<View> ViewVector;

		struct hashview{
			std::size_t operator () (View const &v) const{
				return hash(v);
			}
		};
		struct equalview{
			bool operator () (View const &v1, View const &v2) const{
				return is_equal(v1,v2);
			}
		};
		std::unordered_map<View const, std::pair<Position, Position> const,hashview,equalview> route;

//		std::vector<View> fullViewVector;//the views stored in ViewVector are half-deleted, in some situation where full views are needed, such as get full view areas from each view, this may be helpful.

		Map stepMapOutput(View const &v) ;
		void pushView(View const &v);
		void makeRoute(View const &view);
		


};

}


#endif
