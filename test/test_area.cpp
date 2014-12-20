
#include "area.h"
#include "debug.h"
#include "position.h"
#include "view.h"
#include "obstacle.h"


using namespace robot;

int main(int argc,char **argv){
	Position p1(7,4);
	Position p2(7,0);
	Position p3(5,1);
	Position p4(4,0);
	Position p5(3,4);
	Position p6(1,2);
	Position p7(1,2);
	Area a{p1,p2,p3,p4,p5,p6,p7};
	dbg(a);

	View v{Obstacle(p1,p2),Obstacle(p3,p4),Obstacle(p5,p6)};
	Area b(v);
	dbg(b);

	return 0;
}
