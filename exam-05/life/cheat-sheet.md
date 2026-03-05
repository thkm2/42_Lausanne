# life - Cheat Sheet

## Structure : 3 phases dans main()

### Phase 1 : Lecture stdin
- `calloc(w * h, 4)` pour board `b` et temp `t`
- pen = 0 (UP), px/py = 0
- `x` : toggle pen, si pen DOWN -> marquer cellule
- `w/a/s/d` : deplacer (clampe), si pen DOWN -> marquer
- else : ignorer

### Phase 2 : Game of Life (n iterations)
- Double boucle y/x, compter 8 voisins avec dy/dx (-1 a 1)
- Skip self : `(dx || dy)`
- Regle : `t[i] = (c == 3 || (c == 2 && b[i]))`
- Swap pointeurs b/t (pas de memcpy)

### Phase 3 : Affichage
- `putchar('O')` ou `putchar(' ')` + `putchar('\n')`

## Points cles
- Index tableau plat : `y * w + x`
- dy/dx commencent a -2 avec ++pre dans le while
- Bornes : `y+dy >= 0 && y+dy < h && x+dx >= 0 && x+dx < w`
- `calloc` initialise a 0 (pas besoin de memset)
- Includes : `stdio.h` (putchar) + `stdlib.h` (atoi, calloc) + `unistd.h` (read)





Création du tableau :


itération :
2. Les boucles : parcours des 8 voisins

 dy = -2;
 while (++dy <= 1)       // dy vaut -1, 0, +1
 {
     dx = -2;
     while (++dx <= 1)   // dx vaut -1, 0, +1
 dy et dx commencent à -2 mais sont pré-incrémentés (++dy) avant le test, donc ils parcourent les valeurs -1, 0, +1. Cela forme une
 grille 3x3 autour de la cellule courante :

 (-1,-1) (0,-1) (1,-1)
 (-1, 0) (0, 0) (1, 0)   <-- (0,0) = la cellule elle-même
 (-1,+1) (0,+1) (1,+1)

 3. La condition du if

 if ((dx || dy) && y+dy >= 0 && y+dy < h && x+dx >= 0 && x+dx < w)
 Trois vérifications :
 ┌───────────────────────┬────────────────────────────────────────────────────────────────────┐
 │       Condition       │                                Rôle                                │
 ├───────────────────────┼────────────────────────────────────────────────────────────────────┤
 │ (dx || dy)            │ Exclut la cellule elle-même (quand dx == 0 ET dy == 0, c'est faux) │
 ├───────────────────────┼────────────────────────────────────────────────────────────────────┤
 │ y+dy >= 0 && y+dy < h │ Le voisin ne sort pas de la grille verticalement                   │
 ├───────────────────────┼────────────────────────────────────────────────────────────────────┤
 │ x+dx >= 0 && x+dx < w │ Le voisin ne sort pas de la grille horizontalement                 │
 └───────────────────────┴────────────────────────────────────────────────────────────────────┘
 4. Comptage

 c += b[(y + dy) * w + x + dx];
 b est le tableau 1D représentant la grille. La formule (y + dy) * w + x + dx convertit les coordonnées 2D en index 1D. Si la cellule
 voisine est vivante (valeur 1), c s'incrémente.

 5. La règle du Jeu de la Vie

 t[y * w + x] = (c == 3 || (c == 2 && b[y * w + x]));
 On écrit le résultat dans t (la nouvelle grille) :

 - c == 3 : une cellule avec exactement 3 voisins naît (ou reste vivante)
 - c == 2 && b[y * w + x] : une cellule déjà vivante avec 2 voisins survit
 - Sinon : la cellule meurt (ou reste morte) → l'expression vaut 0

 Ce sont les règles classiques de Conway :
 - Naissance : exactement 3 voisins
 - Survie : 2 ou 3 voisins
 - Mort : moins de 2 (sous-population) ou plus de 3 (surpopulation)
