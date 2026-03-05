#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int ac, char **av)
{
	int w, h, n, px, py, pen, x, y, dx, dy, c, *b, *t, *tmp;
	char ch;

	w = atoi(av[1]); h = atoi(av[2]); n = atoi(av[3]);
	b = calloc(w * h, 4); t = calloc(w * h, 4);
	px = 0; py = 0; pen = 0;
	while (read(0, &ch, 1) == 1)
	{
		if (ch == 'x')
		{
			pen = !pen;
			if (pen) b[py * w + px] = 1;
		}
		else
		{
			if (ch == 'w' && py > 0) py--;
			if (ch == 's' && py < h - 1) py++;
			if (ch == 'a' && px > 0) px--;
			if (ch == 'd' && px < w - 1) px++;
			if (pen) b[py * w + px] = 1;
		}
	}
	while (n-- > 0)
	{
		y = -1;
		while (++y < h)
		{
			x = -1;
			while (++x < w)
			{
				c = 0;
				dy = -2;
				while (++dy <= 1)
				{
					dx = -2;
					while (++dx <= 1)
						if ((dx || dy) && y+dy >= 0 && y+dy < h && x+dx >= 0 && x+dx < w)
							c += b[(y + dy) * w + x + dx];
				}
				t[y * w + x] = (c == 3 || (c == 2 && b[y * w + x]));
			}
		}
		tmp = b; b = t; t = tmp;
	}
	y = -1;
	while (++y < h)
	{
		x = -1;
		while (++x < w)
			putchar(b[y * w + x] ? 'O' : ' ');
		putchar('\n');
	}
	free(b);
	free(t);
}
