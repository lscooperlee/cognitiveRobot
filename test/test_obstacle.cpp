
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

}
