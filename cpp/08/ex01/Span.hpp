#ifndef SPAN_HPP
#define SPAN_HPP

#include <vector>
#include <stdexcept> // runtime_error
#include <algorithm> // sort, min_element, max_element
#include <iterator> // distance
#include <iostream>

class Span {
	private:
		unsigned int		_capacity;
		std::vector<int>	_v;
	public:
		Span();
		Span(unsigned int N);
		Span(const Span &other);
		Span &operator=(const Span &other);
		~Span();

		void addNumber(int nb);

		int shortestSpan() const;
		int longestSpan() const;

		template <typename T>
		void addRange(T firts, T last);
};

template <typename T>
void Span::addRange(T first, T last) {
	int r = std::distance(first, last);
	if (_v.size() + r > _capacity)
		throw std::runtime_error("range too high");
	_v.insert(_v.end(), first, last);
}

#endif