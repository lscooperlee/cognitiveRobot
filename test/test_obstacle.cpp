
#include <vector>
#include <iostream>
#include "obstacle.h"
#include "view.h"
#include "position.h"
#include "area.h"
#include "template.h"

using namespace robot;
using std::cout;
using std::endl;
using std::vector;

int main(int argc,char **argv){

	Obstacle u={Position(4,1),Position(1,4)};
	cout<<u<<endl;

	Obstacle o=Obstacle(1,1,5,5);
	cout<<o<<endl;
	
	Obstacle b("1 2 3 4");
	cout<<b<<endl;

	Obstacle v;
	v.addPosition(Position(1,2));
	v.addPosition(Position(3,4));
	v.addPosition(Position(5,6));
	cout<<v<<endl;

	Obstacle t(-5589.00, -20.00, -5415.00, 75.00);
	Obstacle m=t.transform(Position(-161.21, 972.45), Angle(0));
	cout<<m<<endl;

	Area w({Position(1,1),Position(6,1),Position(6,6),Position(1,6)});

	Obstacle d("0 0 4 4");
	bool bl=is_in_area(d,w);

	cout<<bl<<endl;
	cout<<is_in_area(Obstacle("-1 -1 -5 -5"),w)<<endl;
}
