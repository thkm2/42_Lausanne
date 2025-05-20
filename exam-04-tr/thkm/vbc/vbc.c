/*
Allowed functions: malloc, calloc, realloc, free, printf, isdigit, write

Write a program that print the result of a math expression given as argument.
You must handle operations '+' '*' and the parenthesis.
You don't have to handle whitespaces in the expression.
All the values in the expression will be between 0 and 9 included.
In case of unexpected symbol, you will print "Unexpected token '%c'\n" and exit with code 1. (If the symbol is the end of input you will print: "Unexpexted end of input\n").
This rule also apply in case you find an unexpected '(' or ')'.
In case of syscall failure, you will exit with 1.

You will find in this directory the beginning of the code you need to write.

Examples:
./a.out '(3+2)*4'
20

./a.out '3+2*4'
11

./a.out '((2+1)*3)+4*(2+(3+2))'
37

...
*/

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
		int n = **s - '0';
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
	if (*s != '\0')
		err_token(*s);
	printf("%d\n", n);
	return (0);
}