free :
'+'
'<<'
'>>'

subtile :
'bigint(int n)'
'<'

#include <string>
#include <iostream>
#include <cstdlib>



Stockage : std::string _n en ordre naturel (MSB first)
  1337 est stocke comme "1337". Print = juste os << _n.

 - 1 membre : _n (string)
 - 3 constructeurs (default "0", int, copie) + 1 assignation + 1 destructeur
 - 3 operateurs dans le .cpp (+, shift <<, shift >>)
 - 5 operateurs composes inline (+=, ++pre, ++post, <<=, >>=)
 - 6 comparaisons inline (<, ==, !=, >, <=, >=)
 - 1 friend inline (ostream <<)


Constructeur int : extraire les chiffres un par un

  bigint(int n) : _n(n ? "" : "0") { while (n) { _n = char('0' + n % 10) + _n; n /= 10; } }

  - Si n=0 → _n = "0" directement, le while ne tourne pas
  - Sinon on extrait le dernier chiffre (n % 10), on le colle devant, on divise par 10
  - Ca construit la string de droite a gauche : 1337 → "7" → "37" → "337" → "1337"


Les 3 fonctions du .cpp

  1. operator+ : addition posee (ecole primaire)
     "42" + "1337"
     → aligner :  "0042" + "1337"     (while + "0" devant)
     → boucle de droite a gauche :     (for i = fin → 0)
        chaque colonne : s = a[i] + b[i] + carry
        on garde s % 10, on retient s / 10
     → si carry reste : coller "1" devant
     → mettre le resultat dans r._n

  2. operator<< (shift left) : coller des zeros
     42 << 3  →  "42" + "000"  →  "42000"
     - Si c'est "0" on retourne direct (pas de "0000")
     - Sinon : r._n.append(atoi(o._n.c_str()), '0')

  3. operator>> (shift right) : couper la fin
     1337 >> 2  →  "1337" on coupe 2 a droite  →  "13"
     - Si on coupe tout ou plus → return bigint() (= 0)
     - Sinon : r._n.erase(r._n.size() - n)


Les operateurs composes : tous delegues aux operateurs de base

  +=   →  *this = *this + o;  return *this;
  ++pre →  *this += 1;  return *this;
  ++post → copie, ++(*this), return copie;
  <<=  →  *this = *this << o;  return *this;
  >>=  →  *this = *this >> o;  return *this;


Les 6 comparaisons : seulement < et == sont "vrais", les 4 autres en decoulent

  <    →  taille differente ? comparer les tailles : sinon comparer les strings
  ==   →  _n == o._n
  !=   →  !( == )
  >    →  o < *this       (inverser les cotes)
  <=   →  !(o < *this)    (pas plus grand)
  >=   →  !(*this < o)    (pas plus petit)


Print : friend inline dans la classe

  friend ostream &operator<<(ostream &os, const bigint &b) { return os << b._n; }

  → friend parce que ostream est a gauche, pas bigint
  → inline dans la classe = pas besoin de le mettre dans le .cpp


Le truc pour s'en souvenir (meme regle que vect2)

  ┌──────────────────────┬──────────────┬────────────────┬─────────┐
  │                      │ Se modifie ? │     Retour     │ const ? │
  ├──────────────────────┼──────────────┼────────────────┼─────────┤
  │ Binaire (+, <<, >>)  │ Non          │ nouveau bigint │ oui     │
  ├──────────────────────┼──────────────┼────────────────┼─────────┤
  │ Compose (+=,<<=,>>=) │ Oui          │ bigint& +*this │ non     │
  ├──────────────────────┼──────────────┼────────────────┼─────────┤
  │ Pre ++               │ Oui          │ bigint& +*this │ non     │
  ├──────────────────────┼──────────────┼────────────────┼─────────┤
  │ Post ++              │ Oui          │ copie bigint   │ non     │
  ├──────────────────────┼──────────────┼────────────────┼─────────┤
  │ Comparaisons         │ Non          │ bool           │ oui     │
  └──────────────────────┴──────────────┴────────────────┴─────────┘
  Modifie → reference + *this.  Ne modifie pas → nouveau + const.
