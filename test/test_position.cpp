#include "position.h"
#include "angle.h"

using namespace robot;

int main(int argc, char** argv){
	Position p=Position();
	Position o=Position(1,0);
	Angle a=0.0;
	p.transform(o,a);
}
