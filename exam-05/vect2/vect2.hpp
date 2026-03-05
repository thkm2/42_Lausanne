#ifndef VECT2_HPP
#define VECT2_HPP

#include <iostream>

class vect2 {
	int _x, _y;
public:
	vect2() : _x(0), _y(0) {}
	vect2(int x, int y) : _x(x), _y(y) {}
	vect2(const vect2 &o) : _x(o._x), _y(o._y) {}
	vect2 &operator=(const vect2 &o) { _x = o._x; _y = o._y; return *this; }

	int &operator[](int i) { return i ? _y : _x; }
	const int &operator[](int i) const { return i ? _y : _x; }

	vect2 &operator+=(const vect2 &o) { _x += o._x; _y += o._y; return *this; }
	vect2 &operator-=(const vect2 &o) { _x -= o._x; _y -= o._y; return *this; }
	vect2 &operator*=(int n) { _x *= n; _y *= n; return *this; }

	vect2 operator+(const vect2 &o) const { return vect2(_x + o._x, _y + o._y); }
	vect2 operator-(const vect2 &o) const { return vect2(_x - o._x, _y - o._y); }
	vect2 operator*(int n) const { return vect2(_x * n, _y * n); }
	vect2 operator-() const { return vect2(-_x, -_y); }

	vect2 &operator++() { ++_x; ++_y; return *this; }
	vect2 operator++(int) { vect2 t(*this); ++_x; ++_y; return t; }
	vect2 &operator--() { --_x; --_y; return *this; }
	vect2 operator--(int) { vect2 t(*this); --_x; --_y; return t; }

	bool operator==(const vect2 &o) const { return _x == o._x && _y == o._y; }
	bool operator!=(const vect2 &o) const { return !(*this == o); }
};

std::ostream &operator<<(std::ostream &os, const vect2 &v);
vect2 operator*(int n, const vect2 &v);

#endif
