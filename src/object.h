#ifndef __SRC_OBJECT_H__
#define __SRC_OBJECT_H__

#include <vector>
#include "position.h"
#include "global.h"

namespace robot {


class Object{
	public:
		virtual ~Object(){}
		
		typedef std::vector<Position>::const_iterator const_iterator;
		typedef std::vector<Position>::iterator iterator;

		const_iterator begin() const { return shape.begin();}
		iterator begin() { return shape.begin();}
		const_iterator end() const { return shape.end();}
		iterator end() { return shape.end();}

		Position const &getPosition() const { return position;}

	protected:
		Object(){}
		Object(Object const &obj){ this->shape=obj.shape; this->position=obj.position;}

		Position position;
		std::vector<Position> shape;
};


}
#endif
