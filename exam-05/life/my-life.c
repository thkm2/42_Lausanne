#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int ac, char **av) {
	if (ac != 4) return 1;
	int w, h, n, pen, x, y, sx, sy, c, *b, *sb, *tmp;
	char ch;
	w = atoi(av[1]);
	h = atoi(av[2]);
	n = atoi(av[3]);
	pen = x = y = 0;
	b = calloc(w*h, sizeof(int));
	if (!b) return 1;
	sb = calloc(w*h, sizeof(int));
	if (!sb) {
		free(b);
		return 1;
	}
	// 1. BASE
	while (read(0, &ch, 1) == 1) {
		if (ch == 'x') {
			pen = !pen;
			if (pen) b[y * w + x] = 1;
		}
		if (ch == 'w' && y > 0) y--;
		if (ch == 'a' && x > 0) x--;
		if (ch == 's' && y < h-1) y++;
		if (ch == 'd' && x < w-1) x++;

		if (pen) b[y * w + x] = 1;
	}

	// 2. LIFE
	while (n-- > 0) {
		y = -1;
		while (++y < h) {
			x = -1;
			while (++x < w) {
				c = 0;
				sy = -2;
				while (++sy <= 1) {
					sx = -2;
					while (++sx <= 1) {
						if ((sx || sy) && y+sy >= 0 && x+sx >= 0 && y+sy < h && x+sx < w)
							c += b[(y+sy) * w + x + sx];
					}
				}
				sb[y * w + x] = (c == 3 || (c == 2 && b[y * w + x]));
			}
		}
		tmp = b; b = sb; sb = tmp;
	}

	// 3. PRINT
	y = -1;
	while (++y < h) {
		x = -1;
		while (++x < w) {
			putchar(b[y * w + x] ? 'O' : ' ');
		}
		putchar('\n');
	}

	free(b);
	free(sb);
	return 0;
}
