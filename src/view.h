#ifndef __SRC_VIEW_H__
#define __SRC_VIEW_H__

#include <set>
#include <iostream>
#include "global.h"
#include "obstacle.h"

namespace robot {


class View {

	public:
		View(){}
		View const &transform();
		void insert(Obstacle const &obstacle){obstacles.insert(obstacle);}


		typedef std::multiset<Obstacle>::const_iterator const_iterator;
		
		const_iterator begin() const {return obstacles.begin();}
		const_iterator end() const {return obstacles.end();}

		int size(){return obstacles.size();}

	private:
		std::multiset<Obstacle> obstacles;
};

static inline std::ostream & operator <<(std::ostream &os, View const &view) {
	for(View::const_iterator i=view.begin();i!=view.end();++i){
		Obstacle const &o=*i;
		os<<o<<" ";
	}
	return os;
}

}
#endif
