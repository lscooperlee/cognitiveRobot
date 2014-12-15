
#include <vector>
#include <iostream>
#include "obstacle.h"
#include "view.h"
#include "position.h"

using namespace robot;
using std::cout;
using std::endl;
using std::vector;

int main(int argc,char **argv){

	Obstacle o=Obstacle(1,1,5,5);
	cout<<o<<endl;
	
	Obstacle b("1 2 3 4");
	cout<<b<<endl;

	vector<Position> v;
	v.push_back(Position(1,2));
	v.push_back(Position(3,4));
	v.push_back(Position(5,6));
	Obstacle c(v);
	cout<<c<<endl;

	Obstacle t(-5589.00, -20.00, -5415.00, 75.00);
	Obstacle m=t.transform(Position(-161.21, 972.45), Angle(0));
	cout<<m<<endl;

	vector<Position> w;
	w.push_back(Position(1,1));
	w.push_back(Position(6,1));
	w.push_back(Position(6,6));
	w.push_back(Position(1,6));

	Obstacle d("0 0 4 4");
	bool bl=d.isInArea(w);

	cout<<bl<<endl;
	cout<<Obstacle("-1 -1 -5 -5").isInArea(w)<<endl;
}
