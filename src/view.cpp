#include "view.h"
#include "template.h"

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

bool View::isInArea(Area const &area) const {
	return is_in_area(*this, area);
}

bool View::isOverlapArea(Area const &area) const {
	return is_overlap_area(*this,area);
}

std::vector<Position> View::toPositions() const{
	return to_positions(*this);
}

#if 0
View View::cut(Position const &pos, Angle const &ang) const{
	//a=sin(ang)
	//b=cos(ang)
	//a(x-x0)+b(y-y0)=0 is the function for line.
	//if angle is between -PI/2 and PI/2 any points above this line  will be cut
	//otherwise, any points below this line will be cut
	
	//another method is to choose two max and min points on the line, and choose an max point along the facing angle, anything in the big triangle will be cut 
	View v;

	for(auto const &o:*this){
		bool keep=true;
		for(auto const &p:o){
			int sign=1;
			if(!ang.isAbove()){
				sign=-1;
			}
			double tmp=sign*(ang.sin()*(p.X()-pos.X())+ang.cos()*(p.Y()-pos.Y()));
			if(tmp>0){
				keep=false;
				break;
			}

		}
		if(keep)
			v.addObstacle(o);
	}
	v.putPosition(getPosition());
	v.putAngle(getAngle());

	return v;
}
#endif

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

	std::vector<Position> vp=view.toPositions();
	vp.push_back(view.getPosition());
	Area area(vp);

	return addNewView(area);
}

View View::deleteAreaExtend(View const &view, double distance) const {

	View extview=view.extend(distance);
	extview.addObstacle(Obstacle(extview.getPosition(),extview.getPosition()));
	Area area(extview);
	/*
	static GnuplotDisplay display("filerobot","/tmp/img1");
	static Map m;
	m.addView(view);
	m.addView(area.toView());
	display.display(m);
	*/
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

View View::addNewView(Area const &area) const{
	View v;

	for (auto const &o:*this) {
		if (!o.isOverlapArea(area)) {
			v.addObstacle(o);
		}
	}

	v.putPosition(getPosition());
	v.putAngle(getAngle());

	return v;
	

}
