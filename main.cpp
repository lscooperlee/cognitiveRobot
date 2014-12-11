#include <iostream>
#include "position.h"
#include "robot.h"

using namespace robot;

int main(int argc, char **argv){
	Angle a=5;
	Robot r;
	r.look();
	r.move(Position());
}


