#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void err_end(void) {
	printf("Unexpexted end of input\n");
	exit(1);
}

void err_token(char c) {
	printf("Unexpected token '%c'\n", c);
	exit(1);
}

int plus(char **s);

int parse(char **s) {
	if (**s == '(') {
		(*s)++;
		int n = plus(s);
		if (**s != ')') {
			if (!**s) err_end();
			else err_token(**s);
		}
		(*s)++;
		return (n);
	}
	if (isdigit(**s)) {
		int n = **s -  '0';
		(*s)++;
		return (n);
	}
	if (!**s) err_end();
	else err_token(**s);
	return (0);
}

int multi(char **s) {
	int n = parse(s);
	while (**s == '*') {
		(*s)++;
		n *= parse(s);
	}
	return (n);
}

int plus(char **s) {
	int n = multi(s);
	while (**s == '+') {
		(*s)++;
		n += multi(s);
	}
	return (n);
}

int main(int ac, char **av) {
	if (ac != 2)
		return (0);
	char *s = av[1];
	int n = plus(&s);
	if (*s) 
		err_token(*s);
	printf("%d\n", n);
	return (0);
}