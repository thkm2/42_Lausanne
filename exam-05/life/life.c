#include <stdio.h>   // putchar
#include <stdlib.h>  // atoi, calloc, free
#include <unistd.h>  // read

int main(int ac, char **av)
{
	// w=largeur, h=hauteur, n=nombre de generations
	// px,py = position du curseur (stylo)
	// pen = stylo leve (0) ou pose (1)
	// b = board actuel, t = board temporaire pour le calcul
	int w, h, n, px, py, pen, x, y, dx, dy, c, *b, *t, *tmp;
	char ch;

	// === PHASE 1 : LECTURE DE L'INPUT (dessiner les cellules) ===

	// ./life 5 5 3  ->  grille 5x5, 3 generations
	w = atoi(av[1]); h = atoi(av[2]); n = atoi(av[3]);

	// calloc = malloc + mise a zero. Taille = w*h cases, 4 octets chacune (int)
	// Grille 1D aplatie : la case (x,y) est a l'index [y * w + x]
	//   Exemple grille 3x3 :  [0][1][2]    (y=0)
	//                          [3][4][5]    (y=1)
	//                          [6][7][8]    (y=2)
	//   La case (1,2) = index [2 * 3 + 1] = [7]
	b = calloc(w * h, 4); t = calloc(w * h, 4);

	// Stylo demarre en haut a gauche (0,0), leve (pen=0)
	px = 0; py = 0; pen = 0;

	// Lire l'input caractere par caractere depuis stdin
	// Exemple : "dxss" = droite, poser stylo, bas, bas
	while (read(0, &ch, 1) == 1)
	{
		if (ch == 'x')
		{
			// 'x' = toggle du stylo : 0->1 ou 1->0
			pen = !pen;
			// Si on vient de poser le stylo, on marque la case actuelle
			if (pen) b[py * w + px] = 1;
		}
		else
		{
			// Deplacements WASD (comme un jeu video)
			//   w = haut     (py diminue, pas en dessous de 0)
			//   s = bas      (py augmente, pas au dela de h-1)
			//   a = gauche   (px diminue, pas en dessous de 0)
			//   d = droite   (px augmente, pas au dela de w-1)
			if (ch == 'w' && py > 0) py--;
			if (ch == 's' && py < h - 1) py++;
			if (ch == 'a' && px > 0) px--;
			if (ch == 'd' && px < w - 1) px++;
			// Si le stylo est pose, on laisse une trace en se deplacant
			if (pen) b[py * w + px] = 1;
		}
	}

	// === PHASE 2 : SIMULATION DU JEU DE LA VIE (n generations) ===

	// A chaque generation, on applique les regles sur TOUTES les cellules
	while (n-- > 0)
	{
		// Parcourir chaque cellule de la grille
		// Astuce : y = -1 puis ++y dans le while -> y va de 0 a h-1
		y = -1;
		while (++y < h)
		{
			x = -1;
			while (++x < w)
			{
				// Compter les voisins vivants autour de (x,y)
				// Chaque cellule a 8 voisins (ou moins sur les bords)
				//   [NW][N][NE]      (-1,-1)(0,-1)(1,-1)
				//   [W ][.][E ]  =   (-1, 0)     (1, 0)
				//   [SW][S][SE]      (-1, 1)(0, 1)(1, 1)
				c = 0;
				// dy et dx vont de -1 a 1 (meme astuce : -2 puis ++)
				dy = -2;
				while (++dy <= 1)
				{
					dx = -2;
					while (++dx <= 1)
						// (dx || dy) = skip la cellule elle-meme (0,0)
						// Les 4 conditions = verifier qu'on deborde pas de la grille
						if ((dx || dy) && y+dy >= 0 && y+dy < h && x+dx >= 0 && x+dx < w)
							c += b[(y + dy) * w + x + dx];
				}
				// Les 4 regles du Game of Life condensees en une seule ligne :
				//   - 3 voisins -> vivant (naissance OU survie)
				//   - 2 voisins ET deja vivant -> survie
				//   - Sinon -> mort
				// Exemple : cellule morte + 3 voisins -> c==3 -> 1 (nait)
				// Exemple : cellule vivante + 1 voisin -> c!=3 et c!=2 -> 0 (meurt)
				t[y * w + x] = (c == 3 || (c == 2 && b[y * w + x]));
			}
		}
		// Swap : le board temporaire t devient le nouveau board b
		// Pas besoin de copier, on echange juste les pointeurs
		//   Avant : b -> [ancienne gen]   t -> [nouvelle gen]
		//   Apres : b -> [nouvelle gen]   t -> [ancienne gen] (sera ecrase)
		tmp = b; b = t; t = tmp;
	}

	// === PHASE 3 : AFFICHAGE DU RESULTAT ===

	// Parcourir la grille et afficher 'O' (vivant) ou ' ' (mort)
	y = -1;
	while (++y < h)
	{
		x = -1;
		while (++x < w)
			putchar(b[y * w + x] ? 'O' : ' ');
		// Retour a la ligne apres chaque rangee
		putchar('\n');
	}
	free(b);
	free(t);
}
