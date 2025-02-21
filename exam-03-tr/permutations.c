#include <stdio.h>

int ft_strlen(char *s) {
	int i = 0;
	while (s[i])
		i++;
	return (i);
}

void swap(char *a, char *b) {
	char tmp = *a;
	*a = *b;
	*b = tmp;
}

void perm(char *s, int l, int r) {
	if (l == r)
		printf("%s\n", s);
	int i = l - 1;
	while (++i <= r)
	{
		swap(&s[l], &s[i]);
		perm(s, l + 1, r);
		swap(&s[l], &s[i]);
	}
}

char *sort_s(char *s) {
	int i = -1;
	while (s[++i])
	{
		if (s[i + 1] && s[i] > s[i + 1]) {
			swap(&s[i], &s[i + 1]);
			i = -1;
		}
	}
	return (s);
}

int main(int ac, char **av) {
	if (ac != 2)
		return (1);
	char *s = sort_s(av[1]);
	perm(s, 0, ft_strlen(s) - 1);
	return (0);
}