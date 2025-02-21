#include <unistd.h>
#include <stdlib.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 10
#endif

// vérifier les données entrantes -
// lire tant que y'a nl ou EOF
// à chaque fois qu'on a lu on met dans line
// une fois que y'a eu nl ou EOF tu renvoies la line
// et tu enlèves la line à line
// free tout quand y'a EOF

int is_nl_in(char *s) {
	int i = -1;
	while (s[++i])
		if (s[i] == '\n')
			return (i);
	return (-1);
}

int ft_strlen(char *s) {
	int i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char *ft_strjoin(char **s1, char *s2) {
	int len = ft_strlen(*s1) + ft_strlen(s2);
	char *rs = malloc(sizeof(char) * (len + 1));
	if (!rs || !s2)
		return (NULL);
	int i = 0;
	if (s1[0])
	{
		while (s1[0][i])
		{
			rs[i] = s1[0][i];
			i++;
		}
	}
	int j = -1;
	while (s2[++j])
		rs[i++] = s2[j];
	rs[i] = 0;
	if (*s1)
	{
		free(*s1);
		*s1 = NULL;
	}
	return (rs);
}

char *malloc_until_nl(char *s, int pos) {
	char *rs = malloc(sizeof(char) * (pos + 1));
	if (!rs)
		return (NULL);
	rs[pos] = 0;
	while (--pos > -1)
		rs[pos] = s[pos];
	return (rs);
}

char *ft_strdup(char *s) {
	int len = ft_strlen(s);
	char *rs = malloc(sizeof(char) * (len + 1));
	if (!rs)
		return (NULL);
	rs[len] = 0;
	int i = -1;
	while (s[++i])
		rs[i] = s[i];
	return (rs);
}

char *get_next_line(int fd) {
	char buffer[BUFFER_SIZE + 1];
	static char *line;
	int bytes_read = 0;
	char *rs;
	int nl = 0;
	char *tmp;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	while (1)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(line);
			line = NULL;
			return (NULL);
		}
		buffer[bytes_read] = 0;
		line = ft_strjoin(&line, buffer);
		nl = is_nl_in(line);
		if (!bytes_read)
		{
			if (!line || !*line)
				return (NULL);
			tmp = line;
			line = NULL;
			return (tmp);
		}
		else if (nl != -1)
		{
			rs = malloc_until_nl(line, nl + 1);
			tmp = line;
			line = ft_strdup(line + nl + 1);
			free(tmp);
			tmp = NULL;
			return (rs);
		}
	}
	return (NULL);
}


/* #include <fcntl.h>
#include <stdio.h>
int main(void) {
	int fd = open("file", O_RDONLY);
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	return (0);
} */