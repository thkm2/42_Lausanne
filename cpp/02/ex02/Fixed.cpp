#include "Fixed.hpp"

Fixed::Fixed() : _rawBits(0) {}

Fixed::~Fixed() {}

Fixed::Fixed(const Fixed &other) {
	*this = other;
}

Fixed &Fixed::operator=(const Fixed &other) {
	if (this != &other)
		_rawBits = other._rawBits;
	return *this;
}

int Fixed::getRawBits( void ) const {
	return _rawBits;
}

void Fixed::setRawBits( int const raw ) {
	_rawBits = raw;
}

Fixed::Fixed(const int value) {
	_rawBits = value << _fractionalBits;
}

Fixed::Fixed(const float value) {
	_rawBits = roundf(value * (1 << _fractionalBits));
}

float Fixed::toFloat( void ) const {
	return ((float)(_rawBits) / (float)(1 << _fractionalBits));
}

int Fixed::toInt( void ) const {
	return _rawBits >> _fractionalBits;
}

std::ostream &operator<<(std::ostream &out, const Fixed &value) {
	out << value.toFloat();
	return (out);
}

bool Fixed::operator<(const Fixed &other) const {
	return _rawBits < other._rawBits;
}

bool Fixed::operator>(const Fixed &other) const {
	return _rawBits > other._rawBits;
}

bool Fixed::operator<=(const Fixed &other) const {
	return _rawBits <= other._rawBits;
}

bool Fixed::operator>=(const Fixed &other) const {
	return _rawBits >= other._rawBits;
}

bool Fixed::operator==(const Fixed &other) const {
	return _rawBits == other._rawBits;
}

bool Fixed::operator!=(const Fixed &other) const {
	return _rawBits != other._rawBits;
}

Fixed Fixed::operator+(const Fixed &other) const {
	return Fixed(this->toFloat() + other.toFloat());
}

Fixed Fixed::operator-(const Fixed &other) const {
	return Fixed(this->toFloat() - other.toFloat());
}

Fixed Fixed::operator*(const Fixed &other) const {
	return Fixed(this->toFloat() * other.toFloat());
}

Fixed Fixed::operator/(const Fixed &other) const {
	return Fixed(this->toFloat() / other.toFloat());
}

Fixed &Fixed::operator++() {
	_rawBits++;
	return *this;
}

Fixed &Fixed::operator--() {
	_rawBits--;
	return *this;
}

Fixed Fixed::operator++(int) {
	Fixed tmp = *this;
	_rawBits++;
	return tmp;
}

Fixed Fixed::operator--(int) {
	Fixed tmp = *this;
	_rawBits--;
	return tmp;
}

Fixed &Fixed::min(Fixed &a, Fixed &b) {
	return (a > b ? b : a);
}

const Fixed &Fixed::min(const Fixed &a, const Fixed &b) {
	return (a > b ? b : a);
}

Fixed &Fixed::max(Fixed &a, Fixed &b) {
	return (a < b ? b : a);
}

const Fixed &Fixed::max(const Fixed &a, const Fixed &b) {
	return (a < b ? b : a);
}