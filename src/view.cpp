
#include "view.h"

using namespace robot;

View const View::transform(Position const &cord, Angle const &ycur_ynew) const {
	View nv;
	for(const_iterator i=begin();i!=end();++i){
		Obstacle const &o=*i;
		nv.addObstacle(o.transform(cord,ycur_ynew));
	}
	return nv;
}


		
void View::addObstacle(Obstacle const &obstacle) {
	Obstacles.insert(obstacle);
}

void View::addObstacles(std::multiset < Obstacle > const &obset) {
	Obstacles.insert(obset.begin(), obset.end());
}

void View::putPosition(Position const &position) {
	globalPosition = position;
}
void View::putAngle(Angle const &angle) {
	facingAngle = angle;
}
		
Position const & View::getPosition() const {
	return globalPosition;
}
Angle const & View::getAngle() const {
	return facingAngle;
};

int View::size() {
	return Obstacles.size();
}


View View::operator -(View const &view) const {
	//toArea
	//
	std::vector < Position > area;
	for (const_iterator i = view.begin(); i != view.end(); ++i){
		Obstacle const &o = *i;
		for (Obstacle::const_iterator j = o.begin(); j != o.end(); ++j){
			Position const &p = *j;
			 area.push_back(p);
		}
	}
	View v;
	for (const_iterator i = begin(); i != end(); ++i) {
		Obstacle const &o = *i;
		if (!o.isInArea(area)) {
			v.addObstacle(o);
		}
	}
	return v;
}
