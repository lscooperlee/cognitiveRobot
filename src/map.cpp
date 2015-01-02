#include "map.h"
#include "template.h"
#include "obstacle.h"
#include "position.h"
#include "view.h"
#include "debug.h"

using namespace robot;

Map::Map(std::initializer_list<View> vlist){
	for(auto const v:vlist){
		addView(v);
	}
}

void Map::addView(View const &view) {
	ViewVector.push_back(view);
//	fullViewVector.push_back(view);
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

Map Map::stepMapOutput(View const &v) {
	Map tm(*this);
	tm.addView(v);
	return tm;
}

std::vector<Map> Map::addViewbyFullDeleteAreaExtend(View const &view, double distance) {
//	fullViewVector.push_back(view);
	
	std::vector<Map> stepMap;

	stepMap.push_back(stepMapOutput(view));
	if(ViewVector.size()==0){
		pushView(view);
	}else{
		View nv=view;
		for(auto const &tv:ViewVector){
			nv=nv.deleteAreaExtend(tv,distance);
			stepMap.push_back(stepMapOutput(nv));
		}
		if(nv.size()){
			pushView(nv);
		}
	}

	return stepMap;
}

void Map::makeRoute(View const &view){

	Position const &p1=view.getPosition();
	if(ViewVector.size()==0){
		Position p2(0,max_y(view));
		route.insert(std::make_pair(view,std::make_pair(p1,p2)));
	}else{
		route.insert(std::make_pair(view,view.makeFacingPair(ViewVector.back())));
	}
}

void Map::pushView(View const &view){
	makeRoute(view);
	ViewVector.push_back(view);
}
