
#include "view.h"

using namespace robot;

View::View(std::initializer_list<Obstacle> oblist){
	for(auto const &o:oblist){
		addObstacle(o);
	}
}

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


View View::operator -(View const &view) const {
	//toArea
	//
	std::vector < Position > area;
	for (auto const &o:view){
		for (auto const &p:o){
			 area.push_back(p);
		}
	}

	View v;
	for (auto const &o:*this) {
		if (!o.isInArea(area)) {
			v.addObstacle(o);
		}
	}
	return v;
}

double View::minX() const {
	return min_x(*this);
}

double View::minY() const {
	return min_y(*this);
}

double View::maxX() const {
	return max_x(*this);
}

double View::maxY() const {
	return max_y(*this);
}
