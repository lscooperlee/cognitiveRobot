
#include <set>
#include <iostream>
#include "view.h"
#include "obstacle.h"
#include "position.h"
#include "display.h"

using namespace robot;

int main(int argc,char **argv){
	View v;
	GnuplotDisplay d("testview","/tmp/img");

	v.addObstacle(Obstacle(1,1,3,3));
	v.addObstacle(Obstacle(4,7,3,2));
	v.addObstacle(Obstacle(2,5,6,0));

	std::cout<<v.size()<<std::endl;
	std::cout<<v<<std::endl;
	d.display(v);

	View w=v.transform(Position(0,0), Angle(PI/2));
	std::cout<<w<<std::endl;
	d.display(w);

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
