#include "Serializer.hpp"

int main() {
	Data d = {17};
	Data *p = &d;
	uintptr_t uint = Serializer::serialize(p);
	Data *r = Serializer::deserialize(uint);
	std::cout << "Same address : " << (r == p ? "yes" : "no") << std::endl;
	return 0;
}