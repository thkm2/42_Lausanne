#include "Span.hpp"

Span::Span() : _capacity(0) {}

Span::Span(unsigned int N) : _capacity(N) {}

Span::Span(const Span &other) : _capacity(other._capacity), _v(other._v) {}

Span &Span::operator=(const Span &other) {
	if (this != & other) {
		_v = other._v;
		_capacity = other._capacity;
	}
	return *this;
}

Span::~Span() {}

void Span::addNumber(int nb) {
	if (_v.size() >= _capacity)
		throw std::runtime_error("Span is full");
	_v.push_back(nb);
}

int Span::longestSpan() const {
	if (_v.size() < 2)
		throw std::runtime_error("<2 elements");
    int min = *(std::min_element(_v.begin(), _v.end()));
    int max = *(std::max_element(_v.begin(), _v.end()));
    return (max - min);
}

int Span::shortestSpan() const {
    if (_v.size() < 2)
        throw std::runtime_error("<2 elements");
    std::vector<int> tmp(_v);
    std::sort(tmp.begin(), tmp.end());

    long best = tmp[1] - tmp[0];
    for (unsigned int i = 1; i < tmp.size(); ++i) {
        long s = static_cast<long>(tmp[i]) - static_cast<long>(tmp[i - 1]);
        if (s < best)
			best = s;
    }
    return static_cast<int>(best);
}