#include "position.h"
#include "angle.h"

using robot::Position;

Position const Position::transform(Position const & coordinate, Angle const &ycur_ynew) const{
	/* see the equation*/

	//first move, then turn
	
	Position newp(this->x-coordinate.X(),this->y-coordinate.Y());

	double cos_ynew_yold=ycur_ynew.cos();
	double cos_ynew_xold=(PI/2-ycur_ynew).cos();
	double cos_xnew_xold=ycur_ynew.cos();
	double cos_xnew_yold=(-PI/2-ycur_ynew).cos();

	double newx=newp.X()*cos_xnew_xold+newp.Y()*cos_xnew_yold;
	double newy=newp.X()*cos_ynew_xold+newp.Y()*cos_ynew_yold;

	return Position(newx, newy);

}
