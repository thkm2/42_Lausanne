 - 2 membres : _x, _y
 - 3 constructeurs (default, param, copie) + 1 assignation
 - 2 operator[] (const et non-const) avec le pattern i ? _y : _x
 - 3 opérateurs composés (+=, -=, *=)
 - 3 opérateurs binaires (+, -, *) + 1 unaire (-)
 - 4 incr/décr (pré/post ++ et --)
 - 2 comparaisons (==, !=)
 - 2 free functions dans le .cpp (<< et int * vect2)

 
 1. Opérateur binaire (crée un nouveau résultat)

 TYPE operator OP (PARAM) const { return TYPE(...); }

 - const parce qu'on ne modifie pas l'objet
 - Retourne un nouveau objet

 2. Opérateur composé (modifie en place)

 TYPE &operator OP= (PARAM) { /* modifie _x, _y */ return *this; }

 - Retourne une référence (&) vers soi-même
 - Pas const parce qu'on se modifie
 - Finit toujours par return *this

 3. Pré-incrément/décrément

 TYPE &operator++() { ++_x; ++_y; return *this; }

 - Comme un composé : référence, modifie, return *this
 - Pas de paramètre

 4. Post-incrément/décrément

 TYPE operator++(int) { TYPE t(*this); ++_x; ++_y; return t; }

 - Le int dans les parenthèses c'est juste un marqueur pour distinguer du pré (c'est la convention C++)
 - Retourne une copie de l'ancien état

 Le truc pour s'en souvenir

 Pose-toi la question : est-ce que l'objet se modifie lui-même ?
 ┌──────────────────────┬──────────────┬────────────────┬─────────┐
 │                      │ Se modifie ? │     Retour     │ const ? │
 ├──────────────────────┼──────────────┼────────────────┼─────────┤
 │ Binaire (+, -, *)    │ Non          │ nouveau TYPE   │ oui     │
 ├──────────────────────┼──────────────┼────────────────┼─────────┤
 │ Composé (+=, -=, *=) │ Oui          │ TYPE & + *this │ non     │
 ├──────────────────────┼──────────────┼────────────────┼─────────┤
 │ Pré ++/--            │ Oui          │ TYPE & + *this │ non     │
 ├──────────────────────┼──────────────┼────────────────┼─────────┤
 │ Post ++/--           │ Oui          │ copie TYPE     │ non     │
 ├──────────────────────┼──────────────┼────────────────┼─────────┤
 │ Unaire -             │ Non          │ nouveau TYPE   │ oui     │
 └──────────────────────┴──────────────┴────────────────┴─────────┘
 C'est toujours la même règle : modifie → référence + *this, ne modifie pas → nouveau + const.


std::ostream &operator<<(std::ostream &os, const vect2 &v);
  vect2 operator*(int n, const vect2 &v);

⏺ Ce sont des fonctions en dehors de la classe parce qu'on ne contrôle pas le côté gauche de l'opérateur :

  - std::cout << v → le côté gauche c'est un ostream, pas un vect2
  - 3 * v → le côté gauche c'est un int, pas un vect2

  Si c'était dans la classe, le côté gauche serait toujours *this donc toujours un vect2. Ici on a besoin que le côté gauche soit autre
  chose, donc free function.

[  Pour s'en souvenir : si le vect2 est à droite de l'opérateur → free function.
  ┌────────────┬─────────┬────────┬────────────────┐
  │ Expression │ Gauche  │ Droite │      Où ?      │
  ├────────────┼─────────┼────────┼────────────────┤
  │ v1 + v2    │ vect2   │ vect2  │ dans la classe │
  ├────────────┼─────────┼────────┼────────────────┤
  │ v * 3      │ vect2   │ int    │ dans la classe │
  ├────────────┼─────────┼────────┼────────────────┤
  │ 3 * v      │ int     │ vect2  │ free function  │
  ├────────────┼─────────┼────────┼────────────────┤
  │ cout << v  │ ostream │ vect2  │ free function  │
  --------------------------------------------------](std::ostream &operator<<(std::ostream &os, const vect2 &v);
  vect2 operator*(int n, const vect2 &v);

⏺ Ce sont des fonctions en dehors de la classe parce qu'on ne contrôle pas le côté gauche de l'opérateur :

  - std::cout << v → le côté gauche c'est un ostream, pas un vect2
  - 3 * v → le côté gauche c'est un int, pas un vect2

  Si c'était dans la classe, le côté gauche serait toujours *this donc toujours un vect2. Ici on a besoin que le côté gauche soit autre
  chose, donc free function.

  Pour s'en souvenir : si le vect2 est à droite de l'opérateur → free function.
  ┌────────────┬─────────┬────────┬────────────────┐
  │ Expression │ Gauche  │ Droite │      Où ?      │
  ├────────────┼─────────┼────────┼────────────────┤
  │ v1 + v2    │ vect2   │ vect2  │ dans la classe │
  ├────────────┼─────────┼────────┼────────────────┤
  │ v * 3      │ vect2   │ int    │ dans la classe │
  ├────────────┼─────────┼────────┼────────────────┤
  │ 3 * v      │ int     │ vect2  │ free function  │
  ├────────────┼─────────┼────────┼────────────────┤
  │ cout << v  │ ostream │ vect2  │ free function  │
  └────────────┴─────────┴────────┴────────────────┘
