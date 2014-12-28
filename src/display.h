#ifndef __SRC_DISPLAY_H__
#define __SRC_DISPLAY_H__

#include <set>
#include <fstream>

namespace robot {

class Map;
class View;
class Angle;
class Position;

class Display {
	public:
		virtual ~Display(){};
		virtual void operator () (View const & v, char const * fname=NULL) =0;
		virtual void operator () (Map const & v, char const * fname=NULL) =0;

	protected:
		Display(){}
		Display(Display const &display){}
};


#define PLOT_BORDER_FACTOR 0.05
#define PLOT_RESOLUTION_X  2400
#define PLOT_RESOLUTION_Y  2400
#define PLOT_ROBOT_RATIO 30

class GnuplotDisplay : public Display{
	public:
		GnuplotDisplay(char const *bname, char const *dname=NULL, int res_x = PLOT_RESOLUTION_X, int res_y=PLOT_RESOLUTION_Y);
		GnuplotDisplay(std::string const bname, std::string const dname="", int res_x = PLOT_RESOLUTION_X, int res_y=PLOT_RESOLUTION_Y);

		void operator () (Map const & v, char const * fname=NULL);

		void operator () (View const & v, char const * fname=NULL);

		void displayRobot(bool robot){displayrobot=robot;}

		~GnuplotDisplay(){};
	private:

		std::string color[6]={
			"#000000",
			"#660033",
			"#4c0099",
			"#0066cc",
			"#00ff80",
			"#99ff33"
		};

		template <typename T>
		void maxmin(T const &obs);

		void display_cleanup(std::string name);

		void display_prepare(std::string name) throw(std::string);

		void dump_view(View const &v, std::ofstream &os);
		View draw_robot(Position const &p, Angle const &a);

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

		bool displayrobot=false;

};


}

#endif
