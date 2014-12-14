
#include "filerobot.h"

using std::ifstream;
using std::string;

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
	delete file;
}

View const &FileRobot::look() throw(NoViewException){
	string s;
	std::getline(*file,s);
}
