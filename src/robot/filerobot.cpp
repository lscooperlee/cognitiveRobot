
#include <cstring>
#include <iostream>
#include "filerobot.h"
#include "map.h"
#include "display.h"
#include "debug.h"

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

Map const FileRobot::doMap(int c) {
	return do_map_backward(c);
}

Map const FileRobot::do_map_backward(int c) const{
	Map m;
	std::vector<View> const &vc=doTransform(c);

	auto sameviewvector=getRevisitMap(vc);

	for(auto const vtrans:vc){
		try{
			sameviewvector.at(&vtrans);
		}catch(...){
			std::vector<Map> sm=m.addViewbyFullDeleteAreaExtend(vtrans,500);
			/*
			if(display){
				for(auto const &m:sm){
					(*display)(m);
				}
				std::cout<<"producing backward map "<<count--<<"th"<<std::endl;
			}*/
		}

	}

	return m;
}

std::vector<View> FileRobot::doTransform(int c) const{
	const_reverse_iterator i=crbegin();
	View const &vorig=*i;
	Position coor=vorig.getPosition();
	Angle angle=vorig.getAngle();
	
	c=c==0?size():c;
	int sz=c>size()?size():c;

	std::vector<View> transformedMemory;
	for(auto i=crbegin();sz>0;sz--,++i){
		View const &v=*i;
		//fist step, make the original position into the current View (v)'s coordinates
		//so the current View (v)'s position and angle is the new zero.
		Position oinv=coor.transform(v.getPosition(),v.getAngle());

		//second step, because current View (v) will be transformed into original coordinates,
		//so the angle of the original coordinates in current View (v) is needed
		Angle ainv=-v.getAngle()+angle;
		
		View const vtrans=v.transform(oinv,ainv);

		transformedMemory.push_back(vtrans);
	}

	return transformedMemory;
}

bool FileRobot::isRevisit(View const &cur, View const &last, View const &tv) const {
	Position const &p=cur.makeFacingPair(last).second;
	return is_in_area(p,tv);
}

std::unordered_map<View const *, bool, viewhash, viewequal> FileRobot::getRevisitMap(std::vector<View> const &vc) const {
	std::unordered_map<View const *, bool, viewhash, viewequal> sameviewvector;
	auto lastv=vc.cend();
	for(auto i=vc.cbegin()+1;i!=vc.cend();++i){
		View const &last=*(i-1);
		View const &cur=*i;

		for(auto j=vc.cbegin()+1;j<i-1;++j){
			View const &cv=*j;
			if(isRevisit(cur,last,cv)){
				bool out=false;
				if (i-lastv>1&&lastv!=vc.cend()){
					out=true;
				}
				lastv=i;
				sameviewvector.insert(std::make_pair(&cur,out));
				break;
			}
		}
	}
	sameviewvector.insert(std::make_pair(&*lastv,true));
	return sameviewvector;
}

inline static void get_revisit_map(void){
	/*
	auto tmphash=[](View const *v)->size_t{
		return hash(v->getPosition())+hash(v->getAngle());
	};
	auto tmpequal=[](View const *v, View const *w)->bool{
		return (is_equal(v->getPosition(), w->getPosition())) && (v->getAngle() == w->getAngle());
	};

	std::unordered_map<View const *, View const *, decltype(tmphash), decltype(tmpequal)> sameviewvector(0, tmphash,tmpequal);
	std::unordered_map<View const *, bool, decltype(tmphash), decltype(tmpequal)> endofrevisit(0,tmphash,tmpequal);

	auto lastv=vc.cend();
	for(auto i=vc.cbegin()+1;i!=vc.cend();++i){
		View const &last=*(i-1);
		View const &cur=*i;
		Position const &p=cur.makeFacingPair(last).second;
		for(auto j=vc.cbegin()+1;j<i-1;++j){
			View const &cv=*j;
			if(is_in_area(p,cv)){
				if (i-lastv>1&&lastv!=vc.cend()){
					endofrevisit.insert(std::make_pair(&(*lastv),true));
				}
				lastv=i;
				sameviewvector.insert(std::make_pair(&cur,&cv));
				break;
			}
		}
	}
	endofrevisit.insert(std::make_pair(&(*lastv),true));
	*/
}
