#include "position.h"
#include "angle.h"

using robot::Position;

Position const Position::transform(Position const & coordinate, Angle const &ycur_ynew) const{
	/* see the equation*/
	double cos_ynew_yold=-ycur_ynew.cos();
	double cos_ynew_xold=(PI/2-ycur_ynew).cos();
	double cos_xnew_xold=-ycur_ynew.cos();
	double cos_xnew_yold=(-ycur_ynew-PI/2).cos();

	double newx=this->x*cos_xnew_xold+this->y*cos_xnew_yold;
	double newy=this->x*cos_ynew_xold+this->y*cos_ynew_yold;

	Position p=Position(newx, newy);
	return p-coordinate;
}
