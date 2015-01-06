#include "view.h"
#include "template.h"
#include "debug.h"

using namespace robot;

View::View(std::initializer_list<Obstacle> oblist){
	Obstacles.insert(Obstacles.end(),oblist);
}

View const View::transform(Position const &cord, Angle const &ycur_ynew) const {
	View nv;

	for(auto const &o:*this){
		nv.addObstacle(o.transform(cord,ycur_ynew));
	}
	nv.putPosition(Position(0,0).transform(cord,ycur_ynew));
	nv.putAngle(-ycur_ynew);
	return nv;
}
		
void View::addObstacle(Obstacle const &obstacle) {
	Obstacles.push_back(obstacle);
}

void View::addObstacles(std::vector< Obstacle > const &obset) {
	Obstacles.insert(Obstacles.end(), obset.begin(), obset.end());
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
	Area area(view);
	return addNewView(area);
}

View View::operator +(View const &view) const {
	View v;
	for(auto const &o:view){
		v.addObstacle(o);
	}
	for(auto const &o:*this){
		v.addObstacle(o);
	}
	return v;
}

bool View::operator ==(View const &view) const {
	return is_equal(globalPosition, view.getPosition()) && (facingAngle == view.getAngle());
}

View View::cut(Position const &pos, Angle const &ang) const{
	//a=sin(ang)
	//b=cos(ang)
	//a(x-x0)+b(y-y0)=0 is the function for line.
	//if angle is between -PI/2 and PI/2 any points above this line  will be cut
	//otherwise, any points below this line will be cut
	
	//another method is to choose two max and min points on the line, and choose an max point along the facing angle, anything in the big triangle will be cut 

	Position p1(pos.directPosition(ang,1000000));
	Position p2(pos.directPosition(ang+PI/2,1000000));
	Position p3(pos.directPosition(ang-PI/2,1000000));

	Area const area({p1,p2,p3});

	return addNewView(area);
}
View View::deleteArea(View const &view) const {

	std::vector<Position> vp=to_positions(view);
	vp.push_back(view.getPosition());
	Area area(vp);

	return addNewView(area);
}

View View::deleteAreaExtend(View const &view, double distance) const {

	View extview=view.extend(distance);
	extview.addObstacle(Obstacle(extview.getPosition(),extview.getPosition()));
	Area area(extview);
	return addNewView(area);

}

View View::extend(double distance) const {
	View v;
	Position const &sp=globalPosition;
	for(auto const &o:*this){
		Obstacle newo;
		for(auto const &p:o){
			Angle a(sp,p);
			Position newp=p.directPosition(a, distance);
			newo.addPosition(newp);
		}
		v.addObstacle(newo);
	}
	v.globalPosition=globalPosition;
	v.facingAngle=facingAngle;
	return v;
}

View const View::doSquare() const {
	Position lb(min_x(*this),0);
	Position rb(max_x(*this),0);
	Position lt(min_x(*this),max_y(*this));
	Position rt(max_x(*this),max_y(*this));

	return View{Obstacle{lb,rb},Obstacle{rb,rt},Obstacle{rt,lt},Obstacle{lt,lb}};
}

View View::addNewView(Area const &area) const{
	View v;

	for (auto const &o:*this) {
		if (!is_overlap_area(o,area)) {
			v.addObstacle(o);
		}
	}

	v.putPosition(getPosition());
	v.putAngle(getAngle());

	return v;

}

std::pair<Position, Position> const View::makeFacingPair(View const &v) const {
	Angle const &a=facingAngle;
	Position const &p2=v.getPosition();
	Position const &p1=globalPosition;
	double distance=p1.distance(p2)/2;
	Position p3=p1.directPosition(a,distance);
	return std::make_pair(p1,p3);
}

Position const &View::getRevisitCheckPoint(View const *last) const{
	if(last==nullptr){
		return globalPosition;
	}
	View const nv=*this-*last;
	double distance=std::numeric_limits<double>::max();
	Position const *rp=nullptr;
	Position const op=globalPosition;
	for(auto const &o:nv){
		for(auto const &p:o){
			double d=op.distance(p);
			if(d<distance){
				distance=d;
				rp=&p;
			}
		}
	}
	
	if(rp==nullptr){
		return globalPosition;
	}

	return *rp;
}
