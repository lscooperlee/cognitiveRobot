#include "template.h"
#include "position.h"
#include "obstacle.h"
#include "view.h"

using namespace robot;


Obstacle::Obstacle() {
}

Obstacle::Obstacle(std::initializer_list<Position> &plist) {
	for(auto i=plist.begin();i!=plist.end();i++){
		shape.push_back(*i);
	}
}

Obstacle::Obstacle(std::string const &str) {
	std::string::size_type pos = 0;
	std::string s = str;
	double x, y;
	while (1) {
		try {
			s = s.substr(pos);
			x = std::stod(s, &pos);
			s = s.substr(pos);
			y = std::stod(s, &pos);

			shape.push_back(Position(x, y));
		}
		catch(...) {
			break;
		}

	}

	position = shape.back();
}

Obstacle::Obstacle(Position const &p1, Position const &p2) {
	shape.push_back(p1);
	shape.push_back(p2);
	position = p1;
}

Obstacle::Obstacle(double x1, double y1, double x2, double y2) {
	shape.push_back(Position(x1, y1));
	shape.push_back(Position(x2, y2));
	position = Position(x1, y1);
}

double Obstacle::length() const {
	if (shape.size() < 2) {
		return 0;
	}
	Position const &p1 = shape[0];
	Position const &p2 = shape[1];
	return p1.distance(p2);
}

void Obstacle::addPosition(Position const &position) {
	shape.push_back(position);
}

bool Obstacle::operator <(Obstacle const &obstacle) const {
	return length() < obstacle.length();
}


Obstacle const Obstacle::transform(Position const &cord, Angle const &ycur_ynew) const {
	Obstacle newshape;
	for (Obstacle::const_iterator i = shape.begin(); i != shape.end(); ++i) {
		Position const &p = *i;
		 newshape.addPosition(p.transform(cord, ycur_ynew));
	}
	return newshape;
}

bool Obstacle::isSameObstacle(Obstacle const &o) const {
	Angle const &a1=getAngle();
	Angle const &a2=o.getAngle();
	Angle const &acheck=Angle(PI*5/180);
	
	if((a1-a2)>acheck || (a1-a2) < -acheck){
		return false;
	}

	Position const p1=average_position(*this);
	Position const p2=average_position(o);
	
	if(p1.distance(p2)<400){
		return true;
	}
	return false;
}


Angle const Obstacle::getAngle() const {
	Position const &p1=shape[0];
	Position const &p2=shape[1];
	return Angle(p1,p2);
}
