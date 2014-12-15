#include <iostream>
#include "position.h"
#include "angle.h"

using namespace robot;
using std::cout;
using std::endl;

int main(int argc, char** argv){
	Position p(-5,-5);
	cout<<p<<endl;

	Position o=Position(1,0);
	cout<<o<<endl;

	Angle a=0.0;
	Position p1=p.transform(o,a);
	cout<<"transforming "<<p<<" from new coordinate "<<o<<" and angle "<<a<<" get "<<p1<<endl;

	a=PI/2;
	Position p2=o.transform(p,a);
	cout<<"transforming "<<o<<" from new coordinate "<<p<<" and angle "<<a<<" get "<<p2<<endl;

	o=Position(-161.21, 972.45);

	p=Position(-5589.00,-20.00);
	Position p3=p.transform(o, Angle(0));
	cout<<"transforming "<<p<<" from new coordinate "<<o<<" and angle "<<"0"<<" get "<<p3<<endl;

	p=Position(-5415.00, 75.00);
	Position p4=p.transform(o, Angle(0));
	cout<<"transforming "<<p<<" from new coordinate "<<o<<" and angle "<<"0"<<" get "<<p4<<endl;

	Position m(4,4);
	Position n(3,1);
	cout<<m-n<<endl;
}
