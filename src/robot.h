#ifndef __SRC_ROBOT_H__
#define __SRC_ROBOT_H__

#include "global.h"
#include "object.h"
#include "mind.h"

namespace robot {

class Map;

class Robot: public Mind, public Object{


	public:
		class NoViewException {};
		class FailCreateException {};

		virtual ~Robot() {}
		virtual View const look() throw(NoViewException)=0;
		virtual void move(Position const & pos) {this->position=pos;}
		virtual void memorize (View const & view) {memory.push_back(view);}
		virtual View recall (int id ) const {return memory[id];}

		virtual Map const doMap(int c=0) const = 0;

	protected:
		int size() const {return memory.size();}
		View const &get(int i) const {return memory[i];}

		typedef std::vector<View>::iterator iterator;
		typedef std::vector<View>::const_iterator const_iterator;

		typedef std::vector<View>::reverse_iterator reverse_iterator;
		typedef std::vector<View>::const_reverse_iterator const_reverse_iterator;
		
		const_iterator cbegin() const  {return memory.cbegin();}
		const_iterator cend() const  {return memory.cend();}

		const_reverse_iterator crbegin() const {return memory.crbegin();}
		const_reverse_iterator crend() const {return memory.crend();}

		std::vector<View> memory;


};

}
#endif
