#ifndef __SRC_VIEW_H__
#define __SRC_VIEW_H__

#include <set>
#include <iostream>
#include "global.h"
#include "obstacle.h"
#include "angle.h"

namespace robot {

//class View:public Area
class View {

	public:
		View const transform(Position const &cord, Angle const &ycur_ynew) const;
		
		//depricated
		void insert(Obstacle const &obstacle){Obstacles.insert(obstacle);}

		void addObstacle(Obstacle const &obstacle){Obstacles.insert(obstacle);}
		void addObstacles(std::multiset<Obstacle> const &obset){Obstacles.insert(obset.begin(),obset.end());}

		void putPosition(Position const &position){globalPosition=position;}
		void putAngle(Angle const &angle){facingAngle=angle;}
		
		Position const &getPosition() const {return globalPosition;}
		Angle const &getAngle() const {return facingAngle;};

		typedef std::multiset<Obstacle>::const_iterator const_iterator;
		
		const_iterator begin() const {return Obstacles.begin();}
		const_iterator end() const {return Obstacles.end();}

		int size(){return Obstacles.size();}

		View operator -(View const &view) const {
			//toArea
			std::vector<Position> area;
			for(const_iterator i=view.begin();i!=view.end();++i){
				Obstacle const &o=*i;
				for(Obstacle::const_iterator j=o.begin();j!=o.end();++j){
					Position const &p=*j;
					area.push_back(p);
				}
				
			}
			View v;		
			for(const_iterator i=begin();i!=end();++i){
				Obstacle const &o=*i;
				if(!o.isInArea(area)){
					v.insert(o);
				}
			}
			return v;
		}

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
