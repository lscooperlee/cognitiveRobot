#ifndef __SRC_DISPLAY_H__
#define __SRC_DISPLAY_H__


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
