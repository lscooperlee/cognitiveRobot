
#include <cstring>
#include "filerobot.h"

using namespace robot;
using std::ifstream;
using std::string;
using std::stod;

FileRobot::FileRobot (char const * fname) throw(FailCreateException){
	file=new ifstream;
	file->open(fname,std::ios::in);
	filename=string(fname);
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
			
			v.putPosition(Position(x1,y1));
			v.putAngle(Angle(Position(x1,y1),Position(x2,y2)));
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
//	return do_map_forward(c);
	return do_map_backward(c);
}

Map const FileRobot::do_map_forward(int c) const{
	Map m;

//	const_iterator end = c == 0 ? cend() : cbegin() + c;
//	for(const_iterator i=cbegin();i!=end;++i){
//		View const &v=*i;

	c=c==0?size():c;
	int sz=c>size()?size():c;
	for(int i=0;i<sz;++i){
		View const &v=get(i);	
		m.addView(v.transform(-v.getPosition(),-v.getAngle()));
	}
	return m;
}

Map const FileRobot::do_map_backward(int c) const {
	Map m;

//	const_reverse_iterator end = c == 0 ? crend() : crbegin() + c;
//	for(;i!=end;++i){
//		View const &v=*i;
//

	const_reverse_iterator i=crbegin();
	View const &vorig=*i;
	Position coor=vorig.getPosition();
	Angle angle=vorig.getAngle();

	c=c==0?size():c;
	int sz=c>size()?size():c;
	for(int i=sz-1;i>=0;--i){
		View const &v=get(i);	

		View const vtrans=v.transform(coor-v.getPosition(),angle-v.getAngle());
		m.addView(vtrans);
	}

	return m;
}
