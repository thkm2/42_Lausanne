#include "Fixed.hpp"

Fixed::Fixed() : _rawBits(0) {
	std::cout << "Default constructor called" << std::endl;
}

Fixed::Fixed(const Fixed &other) {
	std::cout << "Copy constructor called" << std::endl;
	*this = other;
}

Fixed &Fixed::operator=(const Fixed &other) {
	std::cout << "Copy assignment operator called" << std::endl;
	if (this != &other)
		_rawBits = other._rawBits;
	return *this;
}

Fixed::~Fixed() {
	std::cout << "Destructor called" << std::endl;
}


int Fixed::getRawBits( void ) const {
	std::cout << "getRawBits member function called" << std::endl;
	return _rawBits;
}

void Fixed::setRawBits( int const raw ) {
	_rawBits = raw;
}

Fixed::Fixed(const int value) {
	std::cout << "Int constructor called" << std::endl;
	_rawBits = value << _fractionalBits;
}

Fixed::Fixed(const float value) {
	std::cout << "Float constructor called" << std::endl;
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
