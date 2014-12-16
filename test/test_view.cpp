
#include <set>
#include <iostream>
#include "view.h"
#include "obstacle.h"
#include "position.h"
#include "display.h"

using namespace robot;

int main(int argc,char **argv){
	View v;
	GnuplotDisplay d("testview","/tmp/img",500,500);
/*
	v.addObstacle(Obstacle(1,1,3,10));
	v.addObstacle(Obstacle(2,3,3,1));
	v.addObstacle(Obstacle(3,1,1,1));
*/
	v.addObstacle(Obstacle(1,1,1,5));
	v.addObstacle(Obstacle(0,1,3,1));

	std::cout<<v.size()<<std::endl;
	std::cout<<v<<std::endl;
	d.display(v,"P00_A00_");

	View w;
	w=v.transform(Position(0,0), Angle(PI/2));
	std::cout<<w<<std::endl;
	d.display(w,"P00_Ap90_");

	w=v.transform(Position(0,0), Angle(-PI/2));
	std::cout<<w<<std::endl;
	d.display(w,"P00_Am90_");

	w=v.transform(Position(0,0), Angle(-3*PI/4));
	std::cout<<w<<std::endl;
	d.display(w,"P00_Am135_");

	w=v.transform(Position(0,0), Angle(3*PI/4));
	std::cout<<w<<std::endl;
	d.display(w,"P00_Ap135_");
	
	w=v.transform(Position(2,0), Angle(0));
	std::cout<<w<<std::endl;
	d.display(w,"P20_Ap00_");

	w=v.transform(Position(2,0), Angle(PI/2));
	std::cout<<w<<std::endl;
	d.display(w,"P20_Ap90_");

	w=v.transform(Position(2,0), Angle(-PI/2));
	std::cout<<w<<std::endl;
	d.display(w,"P20_Am90_");

	w=v.transform(Position(2,0), Angle(-3*PI/4));
	std::cout<<w<<std::endl;
	d.display(w,"P20_Am135_");

	w=v.transform(Position(2,0), Angle(3*PI/4));
	std::cout<<w<<std::endl;
	d.display(w,"P20_Ap135_");
	


	View m;
	m.addObstacle(Obstacle(1,1,1,6));
	m.addObstacle(Obstacle(2,7,5,5));
	m.addObstacle(Obstacle(6,1,8,-1));
	d.display(m);
	
	View i;
	i.addObstacle(Obstacle(3,-1,4,4));
	i.addObstacle(Obstacle(-5,-5,5,-5));
	d.display(i);

	View r=i-m;
	d.display(r);
}
