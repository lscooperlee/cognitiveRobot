#include "map.h"
#include "view.h"
#include "obstacle.h"
#include "display.h"

using namespace robot;


int main(int argc, char **argv){

	Obstacle o1(1,1,3,3);
	Obstacle o2(6,3,8,1);
	Obstacle o3(4,5,5,5);

	Obstacle o4(3,4,3,6);
	Obstacle o5(6,4,6,6);

	View v1={o1,o2,o3};
	View v2={o4,o5};

	Map m{v2,v1};

	GnuplotDisplay d("testmap","/tmp/img",500,500);
	d(m);
}
