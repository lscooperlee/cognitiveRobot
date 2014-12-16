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
		virtual void display(View const & v) =0;
		virtual void display(Map const & v) =0;

	protected:
		Display(){}
		Display(Display const &display){}
};


class GnuplotDisplay {
	public:
		GnuplotDisplay(char const *bname, char const *dname=NULL);

		void display(Map const & v);

		void display(View const & v);

		void maxmin(Obstacle const &obs);

		void display_cleanup(std::string name);

		void display_prepare(std::string name);

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
