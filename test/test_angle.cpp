
#include <iostream>
#include "angle.h"


using namespace robot;
using std::cout;
using std::endl;

int main(int argc, char **argv){
	Angle a=Angle(PI);
	cout << a << " cos:"<< a.cos() << endl;

	Angle b=Angle(PI/2);
	cout << b << " cos:" << b.cos() << endl;

	Angle c=a-b;
	cout << c << endl;

	Angle d=c-PI/4;
	cout << d << " cos:" << d.cos() << endl;

	Angle f=Angle(b-c);
	cout << f << " cos:" << f.cos() << endl;

}
