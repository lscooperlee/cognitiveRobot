#include <set>
#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include "debug.h"
#include "map.h"
#include "obstacle.h"
#include "view.h"
#include "display.h"
#include "template.h"



using namespace robot;

GnuplotDisplay::GnuplotDisplay(char const *bname, char const *dname, int res_x, int res_y){
	id=0,minX=0,minY=0,maxX=0,maxY=0;
	basename=bname;
	if(dname)
		dirname=dname;
	else
		dirname="./";
	
	plot_resolution_x = res_x;
	plot_resolution_y = res_y;
	
	//if empty create
}

GnuplotDisplay::GnuplotDisplay(std::string const bname, std::string const dname, int res_x, int res_y){
	id=0,minX=0,minY=0,maxX=0,maxY=0;
	basename=bname;
	if(dname.empty())
		dirname="./";
	else
		dirname=dname;
	
	plot_resolution_x = res_x;
	plot_resolution_y = res_y;
	
	//if empty create
}

void GnuplotDisplay::operator () (Map const & m, char const *fname) {
	maxmin(m);

	if(!fname)
		fname="Map";

	display_prepare(std::string(fname));
	
	gnuplotfile << "plot ";
	std::ofstream mapdata;

	unsigned int i=0;
	unsigned int j=0;
	for(auto const &v:m){
		std::string tname=dirname+"/"+"tmpmap"+std::to_string(i)+".dat";
		std::string colorstring;
		if(i>=6){ //size of the color array
			colorstring=color[6-1];
		}else{
			colorstring=color[i];
		}
		gnuplotfile << "\""<<tname<<"\""<<" with linespoint linetype rgb "<<"\""<<colorstring<<"\""<<", ";
		mapdata.open(tname);
		dump_view(v,mapdata);
		if(displayrobot==true){
			View r=draw_robot(v.getPosition(), v.getAngle());
//			View r=draw_facing_direction(m.getRouteItem(v));
			dump_view(r,mapdata);
		}
		mapdata.close();
		i++;
		j++;
	}

	display_cleanup(std::string(fname));

}

void GnuplotDisplay::operator () (View const & v, char const *fname) {

	maxmin(v);

	if(!fname)
		fname="View";

	display_prepare(std::string(fname));

	gnuplotfile << "plot \"-\" with linespoint" <<std::endl;
	dump_view(v,gnuplotfile);

	display_cleanup(std::string(fname));
}

template <typename T>
void GnuplotDisplay::maxmin(T const &obs) {
	//assert
	minX = min_x(obs);
	minY = min_y(obs);
	maxX = max_x(obs);
	maxY = max_y(obs);

}

void GnuplotDisplay::display_cleanup(std::string name){
	gnuplotfile.close();
	std::string dataname=dirname+"/"+name+"_"+basename+std::to_string(id)+".dat";
	std::string cmd=std::string("gnuplot ")+dataname;
	system(cmd.c_str());

	minX=0;
	minY=0;
	maxX=0;
	maxY=0;

	++id;

}

void GnuplotDisplay::display_prepare(std::string name) throw (std::string){

	double xRange = maxX - minX;
	double yRange = maxY - minY;
	double diff = yRange - xRange;
	if (diff > 0) {
		minX -= diff / 2.0;
		maxX += diff / 2.0;
	} else {
		minY -= -diff / 2.0;
		maxY += -diff / 2.0;
	}

	// Add a border to the image

	double border = (maxX - minX) * plot_border_factor; // x and y now have the same range
	minX -= border;
	maxX += border;
	minY -= border;
	maxY += border;

	std::string dataname=dirname+"/"+name+"_"+basename+std::to_string(id)+".dat";
	std::string imgname=dirname+"/"+name+"_"+basename+std::to_string(id)+".png";
	
	if(mkdir(dirname.c_str(),0775)){
		if(EEXIST!=errno)
			throw "fail to make folder for output";
	}

	gnuplotfile.open(dataname);
	if(!gnuplotfile){
		throw "fail to create file for gnuplot";
	}

	gnuplotfile << "set terminal png size " << plot_resolution_x <<", "<<plot_resolution_y << " nocrop linewidth 10" <<std::endl;
	gnuplotfile << "set output \""<<imgname<<"\" "<<std::endl;
	gnuplotfile << "set xrange["<<minX<<":"<<maxX<<"]" <<std::endl;
	gnuplotfile << "set yrange["<<minY<<":"<<maxY<<"]" <<std::endl;

}

void GnuplotDisplay::dump_view(View const &v,std::ofstream &os){
	for(auto const &o:v){
		for(auto &p:o){
			os << p << std::endl;
		}
		os << std::endl;
	}
}

View GnuplotDisplay::draw_robot(Position const &p, Angle const &a){
	double robotlen=(maxX-minX)/PLOT_ROBOT_RATIO;
	Position head=p.directPosition(a,robotlen);
	
	Position left=p.directPosition(a-PI/2, robotlen/3);
	Position right=p.directPosition(a+PI/2, robotlen/3);

	View robot({Obstacle(p,head),Obstacle(head,left),Obstacle(head,right),Obstacle(left,right)});
	return robot;
}

View GnuplotDisplay::draw_facing_direction(std::pair<Position, Position> const &pp){
	View facing({Obstacle(pp.first,pp.second)});
	return facing;
}
