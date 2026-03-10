#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

char *get_next_line(int fd);

void print_stars(char *s) {
	while (*s)
	{
		printf("*");
		s++;
	}
	
}

void filter(char *s1, char *s2) {
	int i = -1;
	while (s1[++i])
	{
		int j = 0;
		while (s1[i + j] == s2[j])
		{
			if (s2[j + 1] == '\0')
			{
				print_stars(s2);
				i += j + 1;
			}
			j++;
		}
		printf("%c", s1[i]);
	}
}

int main(int ac, char **av) {
	char *line;

	if (ac < 2)
		return (1);
	while (1)
	{
		line = get_next_line(0);
		if (!line)
			break;
		filter(line, av[1]); // ATTENTION ! La fonction filter ne fonctionne pas correctement (av[1] = a, line = aaa, exit => *a*)
		free(line);
		line = NULL;
	}
	return (0);
}