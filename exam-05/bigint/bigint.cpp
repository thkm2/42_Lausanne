#include "bigint.hpp"
#include <cstdlib>

// Addition posee comme a l'ecole primaire :
//   "42" + "1337"
// 1) On aligne en ajoutant des 0 devant : "0042" + "1337"
// 2) On additionne colonne par colonne de droite a gauche :
//    2+7=9  4+3=7  0+3=3  0+1=1  →  "1379"
//    Si une colonne depasse 9, on garde le chiffre (% 10) et on retient 1 (/ 10)
// 3) S'il reste une retenue a la fin, on colle un "1" devant
bigint bigint::operator+(const bigint &o) const {
	std::string a = _n, b = o._n;
	while (a.size() < b.size()) a = "0" + a;
	while (b.size() < a.size()) b = "0" + b;
	int carry = 0;
	for (int i = a.size() - 1; i >= 0; i--) {
		int s = (a[i] - '0') + (b[i] - '0') + carry;
		a[i] = '0' + s % 10;
		carry = s / 10;
	}
	if (carry) a = "1" + a;
	bigint r;
	r._n = a;
	return r;
}

// Shift left = multiplier par 10^n = coller n zeros a droite
//   42 << 3  →  "42" + "000"  →  "42000"
//   Cas special : 0 << n = 0 (on ne veut pas "0000")
bigint bigint::operator<<(const bigint &o) const {
	if (_n == "0") return *this;
	bigint r(*this);
	r._n.append(atoi(o._n.c_str()), '0');
	return r;
}

// Shift right = diviser par 10^n = couper les n derniers chiffres
//   1337 >> 2  →  "1337" on enleve 2 a droite  →  "13"
//   Si on coupe tout ou plus, il reste 0
bigint bigint::operator>>(const bigint &o) const {
	int n = atoi(o._n.c_str());
	if (n >= (int)_n.size()) return bigint();
	bigint r(*this);
	r._n.erase(r._n.size() - n);
	return r;
}
