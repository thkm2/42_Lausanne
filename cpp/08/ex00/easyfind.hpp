#ifndef EASYFIND_HPP
#define EASYFIND_HPP

#include <algorithm> // find
#include <vector>
#include <iostream>
#include <list>

template <typename T>
typename T::iterator easyfind(T &container, int needle) {
	typename T::iterator it = std::find(container.begin(), container.end(), needle);
	return it; // .end() si pas trouvé
}

template <typename T>
typename T::const_iterator easyfind(const T &container, int needle) {
	typename T::const_iterator it = std::find(container.begin(), container.end(), needle);
	return it; // pareil
}

#endif