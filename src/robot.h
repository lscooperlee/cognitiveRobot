#ifndef __SRC_ROBOT_H__
#define __SRC_ROBOT_H__

#include "global.h"
#include "object.h"
#include "mind.h"
#include "creature.h"
#include "view.h"

namespace robot {

class Robot: public Mind, public Creature {
	public:
		View const & look();
};

}
#endif
