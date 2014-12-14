
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

View const FileRobot::look() throw(NoViewException){
	string l;
	if(!std::getline(*file,l)){
		throw NoViewException();
	}

	//template!!!
	//FileRobot is a 2D robot
	View v;
	string::size_type pos=0;
	string s=l;
	double x1,y1,x2,y2;
	while(1){
		try{
			s=s.substr(pos);
			x1=stod(s,&pos);

			s=s.substr(pos);
			y1=stod(s,&pos);

			s=s.substr(pos);
			x2=stod(s,&pos);

			s=s.substr(pos);
			y2=stod(s,&pos);
			
			Obstacle o(x1,y1,x2,y2);
			v.insert(o);
		}catch(...){
			break;
		}
	}
	return v;
}


