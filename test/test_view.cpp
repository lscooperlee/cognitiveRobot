
#include <vector>
#include "view.h"
#include "obstacle.h"

using namespace robot;

int main(int argc,char **argv){
	std::set<Obstacle> s;
	s.insert(Obstacle(1,1,3,3));
	s.insert(Obstacle(4,7,3,2));
	View v(s);

	v.insert(Obstacle(2,5,6,0));
}
