#ifndef __SRC_POSITION_H__
#define __SRC_POSITION_H__

class Position{
	public:
		Position(): x(0),y(0),z(0) {};
		Position(double x, double y, double z=0);
		/*
		 * by default and convention, there is a implict cordinates position (0,0,0) so that
		 * the value for this position is (x,y,z), 
		 */
		Position const &transform(Position const &cord);
		

	private:
		double x;
		double y;
		double z;
};

#endif
