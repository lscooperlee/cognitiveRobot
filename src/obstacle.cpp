#include <float.h>
#include "position.h"
#include "obstacle.h"

using namespace robot;


Obstacle::Obstacle() {
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

bool Obstacle::size() const {
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
	return size() < obstacle.size();
}

/*
template < typename T >
bool Obstacle::isInArea(T const &t) const {
	for (Obstacle::const_iterator i = shape.begin(); i != shape.end(); ++i) {
		Position const &o = *i;
		if (o.isInArea(t)) {
			return true;
		}
	}
	return false;
}
*/

Obstacle const Obstacle::transform(Position const &cord, Angle const &ycur_ynew) const {
	Obstacle newshape;
	for (Obstacle::const_iterator i = shape.begin(); i != shape.end(); ++i) {
		Position const &p = *i;
		 newshape.addPosition(p.transform(cord, ycur_ynew));
	}
	return newshape;
}

double Obstacle::minX() const {
	double min = DBL_MAX;
	for (Obstacle::const_iterator i = shape.begin(); i != shape.end(); ++i){
		Position const &o = *i;
		 min = o.X() < min ? o.X() : min;
	}
	return min;
}

double Obstacle::minY() const {
	double min = DBL_MAX;
	for (Obstacle::const_iterator i = shape.begin(); i != shape.end(); ++i) {
		Position const &o = *i;
		 min = o.Y() < min ? o.Y() : min;
	}
	return min;
}

double Obstacle::maxX() const {
	double max = -DBL_MAX;
	for (Obstacle::const_iterator i = shape.begin(); i != shape.end(); ++i) {
		Position const &o = *i;
		 max = o.X() > max ? o.X() : max;
	}
	return max;
}

double Obstacle::maxY() const {
	double max = -DBL_MAX;
	for (Obstacle::const_iterator i = shape.begin(); i != shape.end(); ++i) {
		Position const &o = *i;
		 max = o.Y() > max ? o.Y() : max;
	}
	return max;
}
