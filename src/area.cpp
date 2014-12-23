
#include <deque>
#include <set>
#include <iostream>
#include "global.h"
#include "position.h"
#include "area.h"
#include "angle.h"
#include "view.h"

using namespace robot;

Area::Area(std::initializer_list<Position> poslist){
	toArea(poslist);
}

Area::Area(std::vector<Position> posvector){
	toArea(posvector);
}

Area::Area(View const &v){
	for(auto const &o:v){
		for(auto const &p:o){
			points.push_back(p);
		}
	}
}

Area Area::extend(double distance) const {
	
	Position sp(0,0);
	for(auto const &p:*this){
		sp=sp+p;
	}
	sp=sp/this->size();
	
	std::vector<Position> vp;
	for(auto const &p:*this){
		Angle a(sp,p);
		Position newp=p.directPosition(a, distance);
		vp.push_back(newp);
	}
	return Area(vp);
}

View Area::toView() const {
	View v;
	for(unsigned int i=0,j=1;i<size();i++,j++){
		if(j>=size())
			j=0;
		v.addObstacle(Obstacle(points[i],points[j]));
	}
	return v;
}
