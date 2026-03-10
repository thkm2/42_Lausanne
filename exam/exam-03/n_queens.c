#include <stdio.h>
#include <stdlib.h>

void free_n_tabs(char ***tab, int nb) {
	int i = -1;
	while (++i < nb)
	{
		free(tab[0][i]);
		tab[0][i] = NULL;
	}
	free(*tab);
	*tab = NULL;
}

void set_spaces(char *s, int nb) {
	int i = -1;
	while (++i < nb)
	{
		s[i] = '.';
	}
}

char **init_tab(int nb) {
	char **tab = malloc(sizeof(char *) * (nb + 1));
	if (!tab)
		return (NULL);
	tab[nb] = 0;
	int i = -1;
	while (++i < nb)
	{
		tab[i] = malloc(sizeof(char) * (nb + 1));
		if (!tab[i])
			free_n_tabs(&tab, i);
		tab[i][nb] = 0;
		set_spaces(tab[i], nb);
	}
	return (tab);
}

void print_tab(char **tab) {
	int i = -1;
	while (tab[++i])
		printf("%s\n", tab[i]);
}

int ft_abs(int a, int b) {
	int rs = a - b;
	if (rs < 0)
		return (-rs);
	return (rs);
}

int check_diag(char **tab, int y, int x) {
	int i = -1;
	while (tab[++i])
	{
		int j = -1;
		while (tab[i][++j])
		{
			if (tab[i][j] == 'Q' && ft_abs(i, y) == ft_abs(j, x) && i != y && j != x)
				return (0);
		}
	}
	return (1);
}

int check_line(char **tab, int y, int x) {
	int i = -1;
	while (tab[y][++i])
		if (tab[y][i] == 'Q' && i != x)
			return (0);
	return (1);
}

int check_col(char **tab, int y, int x) {
	int i = -1;
	while (tab[++i])
		if (tab[i][x] == 'Q' && i != y)
			return (0);
	return (1);
}

int check_pos(char **tab, int y, int x) {
	if (check_diag(tab, y, x)
		&& check_line(tab, y, x)
		&& check_col(tab, y, x))
		return (1);
	return (0);
}

int n_queens(char **tab, int col, int nb)
{
    int row;
    int count;

    if (col == nb)
    {
        print_tab(tab);
        printf("\n");
        return (1);
    }
    count = 0;
    row = 0;
    while (row < nb)
    {
        if (check_pos(tab, row, col))
        {
            tab[row][col] = 'Q';
            count += n_queens(tab, col + 1, nb);
            tab[row][col] = '.';
        }
        row++;
    }
    return (count);
}

int main(int ac, char **av) {
	if (ac != 2)
		return (1);
	int nb = atoi(av[1]);
	char **tab = init_tab(nb);
	printf("%d solution trouvee\n", n_queens(tab, 0, nb));
	return (0);
}
