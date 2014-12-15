#ifndef __SRC_DISPLAY_H__
#define __SRC_DISPLAY_H__

#include <set>
#include <fstream>
#include "map.h"
#include "obstacle.h"
#include "view.h"



namespace robot {

class Display {
	public:
		virtual ~Display(){};
		virtual void display(View const & v) =0;
		virtual void display(Map const & v) =0;

	protected:
		Display(){}
		Display(Display const &display){}
};


class GnuplotDisplay {
	public:
		GnuplotDisplay(char const *bname, char const *dname=NULL){
			id=0,minX=0,minY=0,maxX=0,maxY=0;
			basename=bname;
			dirname=dname;

			//if empty create
		}

		void display(Map const & v) {
		}

		void display(View const & v) {

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

		
	private:
		void maxmin(Obstacle const &obs) {
			//assert
			minX = obs.minX()<minX?obs.minX():minX;
			minY = obs.minY()<minY?obs.minY():minY;
			maxX = obs.maxX()>maxX?obs.maxX():maxX;
			maxY = obs.maxY()>maxY?obs.maxY():maxY;

		}

		void display_cleanup(std::string name){
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

		void display_prepare(std::string name){

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

		double minX;
		double minY;
		double maxX;
		double maxY;
		int id;

		std::string basename;
		std::string dirname;
		std::ofstream gnuplotfile;

};

#if 0
template <typename T> 
class Display {
	public:
		virtual ~Display();
		virtual void display(T const & t)=0;

	protected:
		Display(){}
		Display(Display const &display){}
};


template <typename T>
class GnuplotDisplay: public Display<T> {
};
#endif

}

#endif
