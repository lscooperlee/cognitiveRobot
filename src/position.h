#ifndef __SRC_POSITION_H__
#define __SRC_POSITION_H__

class Position{
	public:
		Position(): x(0),y(0),z(0) {};
		Position(int x, int y, int z=0);
		int x;
		int y;
		int z;
};

#endif
