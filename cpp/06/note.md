C'est quoi nan, nanf, +inf, +inff, inff ?

nan = not a number (ex: 0/0)
nanf = pareil pour float

inf = infini positif ou négatif pour un double
inff = pareil pour float



C'est static_cast ?

La version c++ du cast normal, c'est plus sur car plus restrictif



C'est quoi uintptr_t ?

un entier non signé assez grand pour contenir n'importe quelle adresse



static_cast = conversion logique et sûre connue à la compilation (ex: double → int).
reinterpret_cast = réinterprétation brute des bits sans vérification (ex: pointeur ↔ entier).
dynamic_cast = conversion polymorphe vérifiée à l’exécution (ex: Base* → Derived*).