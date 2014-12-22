#ifndef __SRC_AREA_H__
#define __SRC_AREA_H__

#include <deque>
#include <set>
#include <iostream>
#include "global.h"
#include "position.h"

namespace robot {

class Position;

class Area {
	public:
		Area(){}
		Area(std::initializer_list<Position> poslist){
			toArea(poslist);
		}
		
		Area(std::vector<Position> posvector){
			toArea(posvector);
		}

		template <typename T>
		Area(T const &t) {
			toArea(t.toPositions());
		}

		typedef std::deque<Position>::iterator iterator;
		typedef std::deque<Position>::const_iterator const_iterator;

		iterator begin() {return points.begin();}
		iterator end() {return points.end();}

		const_iterator begin() const {return points.cbegin();}
		const_iterator end() const {return points.cend();}

		Position const & operator [] (unsigned int i) const {return points[i];}
		
		unsigned int size() const {return points.size();}

	private:
		std::deque<Position> points;
		
		struct comparePositionLessXY{
			bool operator () (Position const *p1, Position const *p2) const {
				if(p1->X()<p2->X()){
					return true;
				}else if(p1->X()==p2->X()&&p1->Y()<p2->Y()){
					return true;
				}
				return false;
			}
		};
	
		template <typename C>
		void toArea(C const &c){

			std::set<Position const *,comparePositionLessXY> tmpset;
			for(auto const &p:c){
				tmpset.insert(&p);
			}

			std::set<Position const *, comparePositionLessXY>::const_iterator i=tmpset.begin();
			points.push_back(**i);

			for(++i;i!=tmpset.cend();++i){
				Position const &p=**i;
				double db=abs(points.front().Y()-p.Y());
				double de=abs(points.back().Y()-p.Y());
				if(db<=de){
					points.push_front(p);
				}else{
					points.push_back(p);
				}
			}

		}

		
};

static inline std::ostream & operator << (std::ostream &os, Area const &area){
	for(auto const &p:area){
		os << p <<" ";
	}
	return os;
}

}
#endif
