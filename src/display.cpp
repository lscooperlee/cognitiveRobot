#include <set>
#include <fstream>
#include "map.h"
#include "obstacle.h"
#include "view.h"
#include "display.h"



using namespace robot;

GnuplotDisplay::GnuplotDisplay(char const *bname, char const *dname){
	id=0,minX=0,minY=0,maxX=0,maxY=0;
	basename=bname;
	dirname=dname;

	//if empty create
}

void GnuplotDisplay::display(Map const & m) {
	View v=m.toView();
}

void GnuplotDisplay::display(View const & v) {

	for(View::const_iterator i=v.begin();i!=v.end();++i){
		maxmin(*i);
	}

	display_prepare(std::string("View"));

	for(View::const_iterator i=v.begin();i!=v.end();++i){
		Obstacle const &o=*i;
		for(Obstacle::const_iterator j=o.begin();j!=o.end();++j){
			Position const &p=*j;
			gnuplotfile << p << std::endl;
		}
		gnuplotfile << std::endl;
	}
	display_cleanup(std::string("View"));
}


void GnuplotDisplay::maxmin(Obstacle const &obs) {
	//assert
	minX = obs.minX()<minX?obs.minX():minX;
	minY = obs.minY()<minY?obs.minY():minY;
	maxX = obs.maxX()>maxX?obs.maxX():maxX;
	maxY = obs.maxY()>maxY?obs.maxY():maxY;

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

void GnuplotDisplay::display_prepare(std::string name){

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
	#define PLOT_BORDER_FACTOR 0.05
	#define PLOT_RESOLUTION_X  2400
	#define PLOT_RESOLUTION_Y  2400

	double border = (maxX - minX) * PLOT_BORDER_FACTOR; // x and y now have the same range
	minX -= border;
	maxX += border;
	minY -= border;
	maxY += border;

	std::string dataname=dirname+"/"+name+"_"+basename+std::to_string(id)+".dat";
	std::string imgname=dirname+"/"+name+"_"+basename+std::to_string(id)+".png";

	gnuplotfile.open(dataname);
	gnuplotfile << "set terminal png size " << PLOT_RESOLUTION_X <<", "<<PLOT_RESOLUTION_Y << " nocrop linewidth 10" <<std::endl;
	gnuplotfile << "set output \""<<imgname<<"\" "<<std::endl;
	gnuplotfile << "set xrange["<<minX<<":"<<maxX<<"]" <<std::endl;
	gnuplotfile << "set yrange["<<minY<<":"<<maxY<<"]" <<std::endl;
	gnuplotfile << "plot \"-\" with linespoint" <<std::endl;

}

