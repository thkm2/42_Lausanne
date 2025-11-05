#include "Array.hpp"

template <typename T>
Array<T>::Array() : _data(0), _size(0) {}

template <typename T>
Array<T>::Array(unsigned int n) : _data(n ? new T[n]() : 0), _size(n) {} // new T[] alloue new T[]() alloue et init par défaut

template <typename T>
Array<T>::Array(const Array &other) : _data(other._size ? new T[other._size]() : 0), _size(other._size) {
	for (unsigned int i = 0; i < _size; i++) {
		_data[i] = other._data[i]; // deep copy
	}
}

template <typename T>
Array<T> &Array<T>::operator=(const Array &other) {
	if (this != &other) {
		T *tmp = other._size ? new T[other._size]() : 0;
		for (unsigned int i = 0; i < other._size; i++) {
			tmp[i] = other._data[i]; // deep copy
		}
		delete[] _data;
		_data = tmp;
		_size = other._size;		
	}
	return *this;
}

template <typename T>
Array<T>::~Array() {
	delete[] _data;
}

template <typename T>
T &Array<T>::operator[](unsigned int i) {
	if (i >= _size)
		throw std::exception();
	return _data[i];
}

template <typename T>
const T &Array<T>::operator[](unsigned int i) const {
	if (i >= _size)
		throw std::exception();
	return _data[i];
}

template <typename T>
unsigned int Array<T>::size() const {
	return _size;
}