
#include <iostream>
#include "position.h"
#include "angle.h"
#include "debug.h"


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
	
	Angle p;

	p=Angle(Position(1,1),Position(2,2));
	cout << p << " cos:" << p.cos() << endl;

	p=Angle(Position(1,1),Position(0,3));
	cout << p << " cos:" << p.cos() << endl;

	p=Angle(Position(1,1),Position(0,0));
	cout << p << " cos:" << p.cos() << endl;

	p=Angle(Position(1,1),Position(3,0));
	cout << p << " cos:" << p.cos() << endl;

	p=Angle(Position(1,1),Position(1,0));
	cout << p << " cos:" << p.cos() << endl;

	dbg(Angle(3*PI/4)-Angle(-3*PI/4),Angle(-3*PI/4)-Angle(3*PI/4));
	dbg(Angle(PI/4)-Angle(-PI/4),Angle(-PI/4)-Angle(PI/4));
	dbg(Angle(3*PI/2)-Angle(-3*PI/2),Angle(-3*PI/2)-Angle(3*PI/2));
	dbg(Angle(-PI/4)-Angle(-3*PI/4),Angle(-3*PI/4)-Angle(-PI/4));

	p=Angle(Position(123,1124),Position(2454,2232));
	Position mm(0,0);
	Position nn=mm.directPosition(p,20);
	Angle p1=Angle(mm,nn);
	dbg(p1,p);

	Position pp1(-215.00,100.17);
	Position pp2(-414.98,97.47);
	p=Angle(pp1,pp2);
	dbg(p,pp1,pp2);

}
