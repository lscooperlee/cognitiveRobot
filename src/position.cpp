#include "position.h"
#include "angle.h"
#include "area.h"

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

bool Position::isOverlapArea(Area const &area) const{
	return isInArea(area);
}

bool Position::isInArea(Area const &area) const{
	unsigned int i,j=area.size()-1;
	bool oddNodes=false;
	for(i=0;i<area.size();++i){
		double xi=area[i].X();
		double xj=area[j].X();
		double yi=area[i].Y();
		double yj=area[j].Y();
		if((yi<y&&yj>=y)||(yj<y&&yi>=y)){
			if(xi+(y-yi)/(yj-yi)*(xj-xi)<x){
				oddNodes=!oddNodes;
			}
		}
		j=i;
	}
	return oddNodes;
}

Position Position::directPosition(Angle const &a, double distance) const{
	double dy=a.cos()*distance;
	double dx=a.sin()*distance;
	return Position(dx+X(),dy+Y());
}

std::vector<Position> Position::toPositions() const {
	std::vector<Position> v;
	v.push_back(*this);
	return v;
}
