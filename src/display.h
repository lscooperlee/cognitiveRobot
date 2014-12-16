#ifndef __SRC_DISPLAY_H__
#define __SRC_DISPLAY_H__

#include <set>
#include <fstream>
#include "map.h"
#include "view.h"



namespace robot {

class Display {
	public:
		virtual ~Display(){};
		virtual void display(View const & v, std::string fname=NULL) =0;
		virtual void display(Map const & v, std::string fname=NULL) =0;

	protected:
		Display(){}
		Display(Display const &display){}
};


#define PLOT_BORDER_FACTOR 0.05
#define PLOT_RESOLUTION_X  2400
#define PLOT_RESOLUTION_Y  2400

class GnuplotDisplay {
	public:
		GnuplotDisplay(char const *bname, char const *dname=NULL, int res_x = PLOT_RESOLUTION_X, int res_y=PLOT_RESOLUTION_Y);

		void display(Map const & v, char const *fname=NULL);

		void display(View const & v, char const *fname=NULL);

		void maxmin(Obstacle const &obs);

		void display_cleanup(std::string name);

		void display_prepare(std::string name);

		double minX;
		double minY;
		double maxX;
		double maxY;
		int id;

		double plot_border_factor = PLOT_BORDER_FACTOR;
		int plot_resolution_x = PLOT_RESOLUTION_X;
		int plot_resolution_y = PLOT_RESOLUTION_Y;

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
