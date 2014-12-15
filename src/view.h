#ifndef __SRC_VIEW_H__
#define __SRC_VIEW_H__

#include <set>
#include <iostream>
#include "global.h"
#include "obstacle.h"
#include "angle.h"

namespace robot {


class View {

	public:
//		View(){}
		View const transform(Position const &cord, Angle const &ycur_ynew) const;
		void insert(Obstacle const &obstacle){Obstacles.insert(obstacle);}
		void putPosition(Position const &position){globalPosition=position;}
		void putAngle(Angle const &angle){facingAngle=angle;}
		
		Position const &getPosition() const {return globalPosition;}
		Angle const &getAngle() const {return facingAngle;};

		typedef std::multiset<Obstacle>::const_iterator const_iterator;
		
		const_iterator begin() const {return Obstacles.begin();}
		const_iterator end() const {return Obstacles.end();}

		int size(){return Obstacles.size();}

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
