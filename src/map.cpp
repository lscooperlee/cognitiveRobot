
#include "map.h"
#include "obstacle.h"
#include "position.h"
#include "view.h"

using namespace robot;

Map::Map(std::initializer_list<View> vlist){
	for(auto const v:vlist){
		addView(v);
	}
}

void Map::addView(View const &view){
	if(ViewVector.size()==0){
		ViewVector.push_back(view);
	}else{
		View const &tv=ViewVector.back();
		View const nv=view-tv;
		ViewVector.push_back(nv);
	}
}

View Map::toView() const{
	View v;
	v.addObstacles(toObstacles());
	return v;
}

std::multiset<Obstacle> Map::toObstacles() const {
	std::multiset<Obstacle> obstacles;
	for(const_iterator i=begin();i!=end();++i){
		View const &v=*i;
		for(View::const_iterator j=v.begin();j!=v.end();++j){
			Obstacle const &o=*j;
			obstacles.insert(o);
		}
	}
	return obstacles;
}

double Map::minX() const {
	return min_x(*this);
}

double Map::minY() const {
	return min_y(*this);
}

double Map::maxX() const {
	return max_x(*this);
}

double Map::maxY() const {
	return max_y(*this);
}
