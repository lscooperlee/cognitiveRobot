
#include <set>
#include <iostream>
#include "view.h"
#include "obstacle.h"
#include "position.h"
#include "display.h"
#include "debug.h"

using namespace robot;

int main(int argc,char **argv){
	GnuplotDisplay d("testview","/tmp/img",500,500);

	View tt={Obstacle(-1,1,-1,2),Obstacle(1,1,1,2)};
	d(tt);
	
	dbg(tt);
	d(tt.cut(Position(0,2),Angle(PI/4)),"P02_AP45");
	d(tt.cut(Position(0,2),Angle(PI/2)),"P02_AP90");
	d(tt.cut(Position(0,2),Angle(-PI/4)),"P02_AM45");
	d(tt.cut(Position(0,2),Angle(-PI/2)),"P02_AM90");

	d(tt.cut(Position(0,1),Angle(3*PI/2)),"P01_AP135");
	d(tt.cut(Position(0,1),Angle(-3*PI/2)),"P01_AM135");

//	return 0;
	View v;
/*
	v.addObstacle(Obstacle(1,1,3,10));
	v.addObstacle(Obstacle(2,3,3,1));
	v.addObstacle(Obstacle(3,1,1,1));
*/
	v.addObstacle(Obstacle(1,1,1,5));
	v.addObstacle(Obstacle(0,1,3,1));

	std::cout<<v.size()<<std::endl;
	std::cout<<v<<std::endl;
	d(v,"P00_A00_");

	View w;
	w=v.transform(Position(0,0), Angle(PI/2));
	std::cout<<w<<std::endl;
	d(w,"P00_Ap90_");

	w=v.transform(Position(0,0), Angle(-PI/2));
	std::cout<<w<<std::endl;
	d(w,"P00_Am90_");

	w=v.transform(Position(0,0), Angle(-3*PI/4));
	std::cout<<w<<std::endl;
	d(w,"P00_Am135_");

	w=v.transform(Position(0,0), Angle(3*PI/4));
	std::cout<<w<<std::endl;
	d(w,"P00_Ap135_");
	
	w=v.transform(Position(2,0), Angle(0));
	std::cout<<w<<std::endl;
	d(w,"P20_Ap00_");

	w=v.transform(Position(2,0), Angle(PI/2));
	std::cout<<w<<std::endl;
	d(w,"P20_Ap90_");

	w=v.transform(Position(2,0), Angle(-PI/2));
	std::cout<<w<<std::endl;
	d(w,"P20_Am90_");

	w=v.transform(Position(2,0), Angle(-3*PI/4));
	std::cout<<w<<std::endl;
	d(w,"P20_Am135_");

	w=v.transform(Position(2,0), Angle(3*PI/4));
	std::cout<<w<<std::endl;
	d(w,"P20_Ap135_");
	
	View m;
	m.addObstacle(Obstacle(1,1,1,6));
	m.addObstacle(Obstacle(2,7,5,5));
	m.addObstacle(Obstacle(6,1,8,-1));
	d(m);
	
	View i;
	i.addObstacle(Obstacle(3,-1,4,4));
	i.addObstacle(Obstacle(-5,-5,5,-5));
	d(i);

	View r=i-m;
	d(r);

	r.addSameSpaceView({&i,&i,&m,&r,&i});
	dbg("r",&r);
	unsigned int size=r.getSameSpaceSize();
	for(unsigned int k=0;k<size;k++){
		dbg(k,r.getSameSpaceView(k));
	}
}
