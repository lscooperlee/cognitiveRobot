#ifndef __SRC_DEBUG_H__
#define __SRC_DEBUG_H__

#if defined(DEBUG)
#include <iostream>

namespace robot {

template <typename T>
void dbg(const T& arg){
	std::cout << arg << std::endl;
}

template <typename T, typename... Types>
void dbg(const T& firstArg, const Types&... args){
	std::cout << firstArg << " ";
	dbg(args...);
}

}
#endif

#endif
