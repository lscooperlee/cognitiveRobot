#ifndef __SRC_MIND_H__
#define __SRC_MIND_H__

#include <vector>
#include "global.h"
#include "view.h"

namespace robot {

class Mind {

	
	public:
		virtual ~Mind() {}
	
	protected:
		Mind() {}
		Mind(Mind const &mind) {}

};


}
#endif
