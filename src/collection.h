#ifndef __SRC_COLLECTION_H__
#define __SRC_COLLECTION_H__

#include <vector>
#include <set>
#include "global.h"

namespace robot {


template<typename T>
class Collection {
	public:
		typedef typename std::vector<T>::const_iterator const_iterator;
		typedef typename std::vector<T>::const_reverse_iterator const_reverse_iterator;
		typedef typename std::vector<T>::iterator iterator;
		typedef typename std::vector<T>::reverse_iterator reverse_iterator;

		iterator begin() const { return s.begin();}
		const_iterator cbegin() const { return s.begin();}

		iterator end() const { return s.end();}
		const_iterator cend() const { return s.end();}

	private:
		std::vector<T> s; 		//sequence
};

}

#endif
