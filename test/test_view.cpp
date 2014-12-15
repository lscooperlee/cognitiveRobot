
#include <set>
#include "view.h"
#include "obstacle.h"
#include "position.h"
#include "display.h"

using namespace robot;

int main(int argc,char **argv){
	View v;
	GnuplotDisplay d("testview","/tmp/img");

	v.insert(Obstacle(1,1,3,3));
	v.insert(Obstacle(4,7,3,2));
	v.insert(Obstacle(2,5,6,0));

	std::cout<<v.size()<<std::endl;
	std::cout<<v<<std::endl;
	d.display(v);

	View w=v.transform(Position(0,0), Angle(PI/2));
	std::cout<<w<<std::endl;
	d.display(w);

	View m;
	m.insert(Obstacle(1,1,1,6));
	m.insert(Obstacle(2,7,5,5));
	m.insert(Obstacle(6,1,8,-1));
	d.display(m);
	
	View i;
	i.insert(Obstacle(3,-1,4,4));
	i.insert(Obstacle(-5,-5,5,-5));
	d.display(i);

	View r=i-m;
	d.display(r);
}
