
#include <set>
#include "view.h"
#include "obstacle.h"

using namespace robot;

int main(int argc,char **argv){
	View v;

	v.insert(Obstacle(1,1,3,3));
	v.insert(Obstacle(4,7,3,2));
	v.insert(Obstacle(2,5,6,0));

	std::cout<<v.size()<<std::endl;
	std::cout<<v<<std::endl;
}
