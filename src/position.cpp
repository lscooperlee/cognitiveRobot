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

bool Position::isInArea(std::vector<Position> const &t) const{
	unsigned int i,j=t.size()-1;
	bool oddNodes=false;
	for(i=0;i<t.size();++i){
		double xi=t[i].X();
		double xj=t[j].X();
		double yi=t[i].Y();
		double yj=t[j].Y();
		if((yi<y&&yj>=y)||(yj<y&&yi>=y)){
			if(xi+(y-yi)/(yj-yi)*(xj-xi)<x){
				oddNodes=!oddNodes;
			}
		}
		j=i;
	}
	return oddNodes;
}
