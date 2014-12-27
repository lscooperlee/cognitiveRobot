
#include <cstring>
#include "filerobot.h"
#include "map.h"

using namespace robot;
using std::ifstream;
using std::string;
using std::stod;

FileRobot::FileRobot (char const * fname) throw(FailCreateException){
	file=new ifstream;
	file->open(fname,std::ios::in);
	filename=string(fname);
	if(file->fail())
		throw(FailCreateException());
}

FileRobot::FileRobot (string const fname) throw(FailCreateException){
	file=new ifstream;
	file->open(fname,std::ios::in);
	filename=fname;
	if(file->fail())
		throw(FailCreateException());
}

FileRobot::FileRobot (FileRobot const &filerobot) {
	filename=filerobot.filename;
	file=new ifstream;
	file->open(filename.c_str(),std::ios::in);
}

FileRobot::~FileRobot(){
	file->close();
	delete file;
}

View const FileRobot::look() throw(NoViewException) {
	string l;
	View v;
	string::size_type pos = 0;

	if (!std::getline(*file, l)) {
		throw NoViewException();
	}

	if (l.find("robotObject:") == 0) {
		double x1, y1, x2, y2;
		string s = l;
		pos=std::strlen("robotObject:");
		try {
			s = s.substr(pos);
			x1 = stod(s, &pos);

			s = s.substr(pos);
			y1 = stod(s, &pos);

			s = s.substr(pos);
			x2 = stod(s, &pos);

			s = s.substr(pos);
			y2 = stod(s, &pos);
			
			Position p1(x1,y1);
			Position p2(x2,y2);
			Angle a(p1,p2);
			v.putAngle(a);
			v.putPosition(Position(x1,y1));
		}
		catch( ...) {
			return v;
		}
	}

	if (!std::getline(*file, l)) {
		throw NoViewException();
	}

		//template!!!
		//FileRobot is a 2D robot
	if (l.find("Obstacles:") == 0) {
		string s = l;
		pos=std::strlen("Obstacles:");
		double x1, y1, x2, y2;
		while (1) {
			try {
				s = s.substr(pos);
				x1 = stod(s, &pos);

				s = s.substr(pos);
				y1 = stod(s, &pos);

				s = s.substr(pos);
				x2 = stod(s, &pos);

				s = s.substr(pos);
				y2 = stod(s, &pos);

				Obstacle o(x1, y1, x2, y2);
				v.addObstacle(o);
			}
			catch( ...) {
				break;
			}
		}
	}
	return v;
}

Map const FileRobot::doMap(int c) const{
	return do_map_backward(c);
}

/*
Map const FileRobot::do_map_forward(int c) const{
	Map m;

	c=c==0?size():c;
	int sz=c>size()?size():c;
	for(int i=0;i<sz;++i){
		View const &v=get(i);	
		m.addView(v.transform(-v.getPosition(),-v.getAngle()));
	}
	return m;
}
*/

Map const FileRobot::do_map_backward(int c) const {
	Map m;

	const_reverse_iterator i=crbegin();
	View const &vorig=*i;
	Position coor=vorig.getPosition();
	Angle angle=vorig.getAngle();
	
	c=c==0?size():c;
	int sz=c>size()?size():c;

	int j=sz;
	for(auto i=crbegin();j>0;j--,++i){
		View const &v=*i;
		//fist step, make the original position into the current View (v)'s coordinates
		//so the current View (v)'s position and angle is the new zero.
		Position oinv=coor.transform(v.getPosition(),v.getAngle());

		//second step, because current View (v) will be transformed into original coordinates,
		//so the angle of the original coordinates in current View (v) is needed
		Angle ainv=-v.getAngle()+angle;
		
		View const vtrans=v.transform(oinv,ainv);

		m.addViewbyFullDeleteAreaExtend(vtrans,500, display);

	}

	return m;
}
