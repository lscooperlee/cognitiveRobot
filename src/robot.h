#ifndef __SRC_ROBOT_H__
#define __SRC_ROBOT_H__

#include "global.h"
#include "object.h"
#include "mind.h"
#include "map.h"
#include "view.h"
#include "display.h"

namespace robot {

class Robot: public Mind, public Object{


	public:
		class NoViewException {};
		class FailCreateException {};

		virtual ~Robot() {}
		virtual View const &look() throw(NoViewException)=0;
		virtual void move(Position const & pos) {this->position=pos;}
		virtual void memorize (View const & view) {memory.push_back(view);}
		virtual View recall (int id ) const {return memory[id];}
	//	virtual Map doMap () const {}

	protected:

		typedef std::vector<View>::iterator iterator;
		typedef std::vector<View>::const_iterator const_iterator;
		
		const_iterator begin() const  {return memory.begin();}
		const_iterator end() const  {return memory.end();}

		std::vector<View> memory;

};

}
#endif
