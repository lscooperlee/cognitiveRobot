
#include "view.h"

using robot::View;

View const View::transform(Position const &cord, Angle const &ycur_ynew) const {
	View nv;
	for(const_iterator i=begin();i!=end();++i){
		Obstacle const &o=*i;
		nv.insert(o.transform(cord,ycur_ynew));
	}
	return nv;
}
