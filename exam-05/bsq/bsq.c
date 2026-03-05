#include "bsq.h"

int	err(void)
{
	printf("Error: invalid map\n");
	return (1);
}

void	free_grid(char **g, int n)
{
	int	i;

	i = 0;
	while (i < n)
		free(g[i++]);
	free(g);
}

int	min3(int a, int b, int c)
{
	if (a < b)
		return (a < c ? a : c);
	return (b < c ? b : c);
}

void	solve(char **g, int r, int c, char o, char f)
{
	int	*dp;
	int	i;
	int	j;
	int	max;
	int	bi;
	int	bj;

	dp = calloc(r * c, sizeof(int));
	max = 0;
	bi = 0;
	bj = 0;
	i = -1;
	while (++i < r)
	{
		j = -1;
		while (++j < c)
		{
			if (g[i][j] == o)
				dp[i * c + j] = 0;
			else if (i == 0 || j == 0)
				dp[i * c + j] = 1;
			else
				dp[i * c + j] = min3(dp[(i - 1) * c + j],
						dp[i * c + j - 1],
						dp[(i - 1) * c + j - 1]) + 1;
			if (dp[i * c + j] > max)
			{
				max = dp[i * c + j];
				bi = i;
				bj = j;
			}
		}
	}
	free(dp);
	i = bi - max + 1;
	while (i <= bi)
	{
		j = bj - max + 1;
		while (j <= bj)
			g[i][j++] = f;
		i++;
	}
	i = 0;
	while (i < r)
		printf("%s\n", g[i++]);
}

int	process(FILE *fp)
{
	int		rows;
	char	e;
	char	o;
	char	f;
	char	**g;
	char	*line;
	size_t	len;
	int		cols;
	int		i;

	if (fscanf(fp, "%d %c %c %c", &rows, &e, &o, &f) != 4)
		return (err());
	if (rows <= 0 || e == o || e == f || o == f)
		return (err());
	line = NULL;
	len = 0;
	if (getline(&line, &len, fp) < 0)
		return (free(line), err());
	free(line);
	g = malloc(sizeof(char *) * rows);
	cols = -1;
	i = 0;
	while (i < rows)
	{
		line = NULL;
		len = 0;
		if (getline(&line, &len, fp) < 0)
			return (free_grid(g, i), free(line), err());
		if (line[0] && line[strlen(line) - 1] == '\n')
			line[strlen(line) - 1] = '\0';
		if (cols == -1)
			cols = strlen(line);
		if ((int)strlen(line) != cols || cols == 0)
			return (free_grid(g, i), free(line), err());
		{
			int k = 0;
			while (line[k])
			{
				if (line[k] != e && line[k] != o)
					return (free_grid(g, i), free(line), err());
				k++;
			}
		}
		g[i++] = line;
	}
	solve(g, rows, cols, o, f);
	free_grid(g, rows);
	return (0);
}

int	main(int argc, char **argv)
{
	int		i;
	FILE	*fp;
	int		ret;

	ret = 0;
	if (argc == 1)
		ret = process(stdin);
	else
	{
		i = 1;
		while (i < argc)
		{
			if (i > 1)
				printf("\n");
			fp = fopen(argv[i], "r");
			if (!fp)
				ret = err();
			else
			{
				if (process(fp))
					ret = 1;
				fclose(fp);
			}
			i++;
		}
	}
	return (ret);
}
