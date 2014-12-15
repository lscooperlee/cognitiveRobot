#ifndef __SRC_DISPLAY_H__
#define __SRC_DISPLAY_H__

#include <set>
#include <fstream>
#include "obstacle.h"
#include "view.h"



namespace robot {

template <typename T> 
class Display {
	public:
		virtual ~Display(){};
		virtual void display(View const & v) =0;

	protected:
		Display(){}
		Display(Display const &display){}
};


template <typename T> 
class GnuplotDisplay {
	public:
		void display(T const & v) {
			for(View::const_iterator i=v.begin();i!=v.end();++i){
				maxmin(*i);
			}

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
			
			std::ofstream gnuplotfile;
			gnuplotfile.open("/tmp/gnuplotfile.dat");

			gnuplotfile << "set terminal png size " << PLOT_RESOLUTION_X <<", "<<PLOT_RESOLUTION_Y << " nocrop linewidth 10" <<std::endl;
			gnuplotfile << "set output \"/tmp/a.png\" "<<std::endl;
			gnuplotfile << "set xrange["<<minX<<":"<<maxX<<"]" <<std::endl;
			gnuplotfile << "set yrange["<<minY<<":"<<maxY<<"]" <<std::endl;
			gnuplotfile << "plot \"-\" with linespoint" <<std::endl;

			for(View::const_iterator i=v.begin();i!=v.end();++i){
				Obstacle const &o=*i;
				for(Obstacle::const_iterator j=o.begin();j!=o.end();++j){
					Position const &p=*j;
					gnuplotfile << p << std::endl;
				}
				gnuplotfile << std::endl;
			}

			gnuplotfile.close();

			system("gnuplot /tmp/gnuplotfile.dat");
		}

	private:
		void maxmin(Obstacle const &obs) {
			//assert
			minX = obs.minX()<minX?obs.minX():minX;
			minY = obs.minY()<minY?obs.minY():minY;
			maxX = obs.maxX()>maxX?obs.maxX():maxX;
			maxY = obs.maxY()>maxY?obs.maxY():maxY;

		}
		double minX=0;
		double minY=0;
		double maxX=0;
		double maxY=0;

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
