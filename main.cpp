#include <iostream>
#include "position.h"
#include "robot.h"

using namespace robot;

int main(int argc, char **argv){
	Robot r;
	r.look();
	r.move(Position());
}


