#include "map.h"
#include "template.h"
#include "obstacle.h"
#include "position.h"
#include "view.h"
#include "display.h"

using namespace robot;

Map::Map(std::initializer_list<View> vlist){
	for(auto const v:vlist){
		addView(v);
	}
}

void Map::addView(View const &view) {
	ViewVector.push_back(view);
}


void Map::addViewbyCut(View const &view) {

	if(ViewVector.size()==0){
		ViewVector.push_back(view);
	}else{
		View const &tv=ViewVector.back();
		View const nv=view.cut(tv.getPosition(),tv.getAngle());
		if(nv.size()){
			ViewVector.push_back(nv);
		}
	}
}

void Map::addViewbyFullCut(View const &view) {

	if(ViewVector.size()==0){
		ViewVector.push_back(view);
	}else{
		View nv=view;
		for(auto const &tv:ViewVector){
			nv=nv.cut(tv.getPosition(),tv.getAngle());
		}
		if(nv.size()){
			ViewVector.push_back(nv);
		}
	}
}

void Map::addViewbyFullDeleteArea(View const &view) {
	if(ViewVector.size()==0){
		ViewVector.push_back(view);
	}else{
		View nv=view;
		for(auto const &tv:ViewVector){
			nv=nv.deleteArea(tv);
		}
		if(nv.size()){
			ViewVector.push_back(nv);
		}
	}
}

Map Map::stepMapOutput(View const &v) const {
	Map tm(*this);
	tm.addView(v);
	return tm;
}

std::vector<Map> Map::addViewbyFullDeleteAreaExtend(View const &view, double distance) {
	
	std::vector<Map> stepMap;

	stepMap.push_back(stepMapOutput(view));
	if(ViewVector.size()==0){
		ViewVector.push_back(view);
	}else{
		View nv=view;
		for(auto const &tv:ViewVector){
			nv=nv.deleteAreaExtend(tv,distance);
			stepMap.push_back(stepMapOutput(nv));
		}
		if(nv.size()){
			ViewVector.push_back(nv);
		}
	}

	return stepMap;
}

std::vector<Position> Map::toPositions() const{
	return to_positions(*this);
}

/*
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
*/
