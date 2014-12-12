#ifndef __SRC_ROBOT_H__
#define __SRC_ROBOT_H__

#include "global.h"
#include "object.h"
#include "mind.h"
#include "view.h"

namespace robot {

class Robot: public Mind, public Object{

	public:
		virtual ~Robot(){}
		virtual View const &look()=0;
		virtual void move(Position const & pos){this->position=pos;}

};

}
#endif
