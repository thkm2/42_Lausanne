#ifndef BIGINT_HPP
#define BIGINT_HPP

#include <string>
#include <iostream>

class bigint {
	std::string _n;
public:
	bigint() : _n("0") {}
	bigint(int n) : _n(n ? "" : "0") { while (n) { _n = char('0' + n % 10) + _n; n /= 10; } }
	bigint(const bigint &o) : _n(o._n) {}
	bigint &operator=(const bigint &o) { _n = o._n; return *this; }
	~bigint() {}

	bigint operator+(const bigint &o) const;
	bigint operator<<(const bigint &o) const;
	bigint operator>>(const bigint &o) const;

	bigint &operator+=(const bigint &o) { *this = *this + o; return *this; }
	bigint &operator++() { *this += 1; return *this; }
	bigint operator++(int) { bigint t(*this); ++(*this); return t; }
	bigint &operator<<=(const bigint &o) { *this = *this << o; return *this; }
	bigint &operator>>=(const bigint &o) { *this = *this >> o; return *this; }

	bool operator<(const bigint &o) const { return _n.size() != o._n.size() ? _n.size() < o._n.size() : _n < o._n; }
	bool operator==(const bigint &o) const { return _n == o._n; }
	bool operator!=(const bigint &o) const { return !(*this == o); }
	bool operator>(const bigint &o) const { return o < *this; }
	bool operator<=(const bigint &o) const { return !(o < *this); }
	bool operator>=(const bigint &o) const { return !(*this < o); }

	friend std::ostream &operator<<(std::ostream &os, const bigint &b) { return os << b._n; }
};

#endif
