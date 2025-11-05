#ifndef WHATEVER_HPP
#define WHATEVER_HPP

template <typename T> // ou <class T>
void swap(T &v1, T &v2) { // ref pour pas de copie
	T tmp = v1;
	v1 = v2;
	v2 = tmp;
}

template <typename T>
T min(T &v1, T &v2) {
	return (v1 < v2 ? v1 : v2);
}

template <typename T>
T max(T &v1, T &v2) {
	return (v1 > v2 ? v1 : v2);
}

#endif