#include "vect2.hpp"

std::ostream &operator<<(std::ostream &os, const vect2 &v) {
	os << "{" << v[0] << ", " << v[1] << "}";
	return os;
}

vect2 operator*(int n, const vect2 &v) {
	return v * n;
}
