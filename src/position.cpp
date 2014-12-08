#include "position.h"


Position::Position(double x, double y, double z){
	this->x=x;
	this->y=y;
	this->z=z;
}

Position const & Position::transform(Position const & coordinate){
}
