#include <iostream>
#include "position.h"
#include "angle.h"

using namespace robot;
using std::cout;
using std::endl;

int main(int argc, char** argv){
	Position p;//=Position();
	cout<<p<<endl;

	Position o=Position(1,0);
	cout<<o<<endl;

	Angle a=0.0;
	Position p1=p.transform(o,a);
	cout<<"transforming "<<p<<" from new coordinate "<<o<<" and angle "<<a<<" get "<<p1<<endl;

	a=PI/2;
	Position p2=o.transform(p,a);
	cout<<"transforming "<<o<<" from new coordinate "<<p<<" and angle "<<a<<" get "<<p2<<endl;
}
