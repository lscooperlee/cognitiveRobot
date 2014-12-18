#include "view.h"

using namespace robot;

View::View(std::initializer_list<Obstacle> oblist){
	for(auto const &o:oblist){
		addObstacle(o);
	}
}

View const View::transform(Position const &cord, Angle const &ycur_ynew) const {
	View nv;

	for(auto const &o:*this){
		nv.addObstacle(o.transform(cord,ycur_ynew));
	}
//	nv.putPosition(getPosition().transform(cord,ycur_ynew));
	nv.putPosition(Position(0,0).transform(cord,ycur_ynew));
	nv.putAngle(-ycur_ynew);
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

View View::cut(Position const &pos, Angle const &ang) const{
	//a=sin(ang)
	//b=cos(ang)
	//a(x-x0)+b(y-y0)=0 is the function for line.
	//if angle is between -PI/2 and PI/2 any points above this line  will be cut
	//otherwise, any points below this line will be cut
	
	//another method is to choose two max and min points on the line, and choose an max point along the facing angle, anything in the big triangle will be cut 
	View v;

	for(auto const &o:*this){
		dbg(o);
		bool keep=true;
		for(auto const &p:o){
			dbg(p);
			int sign=1;
			if(!ang.isAbove()){
				sign=-1;
			}
			double tmp=sign*(ang.sin()*(p.X()-pos.X())+ang.cos()*(p.Y()-pos.Y()));
			dbg(p,ang,sign,tmp);
			if(tmp>0){
				keep=false;
				break;
			}

		}
		if(keep)
			v.addObstacle(o);
		dbg("\n");
	}
	v.putPosition(getPosition());
	v.putAngle(getAngle());

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
