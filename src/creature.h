#ifndef __SRC_CREATURE_H__
#define __SRC_CREATURE_H__


#include "global.h"
#include "object.h"
#include "view.h"
#include "position.h"

class Creature: public Object {
	public:
		virtual View const &look() = 0;
		virtual void move(Position const & pos){this->position=pos;}
};

#endif


