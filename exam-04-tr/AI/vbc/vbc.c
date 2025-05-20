#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void err_tok(char c) {
    printf("Unexpected token '%c'\n", c);
    exit(1);
}

void err_end(void) {
    printf("Unexpected end of input\n");
    exit(1);
}

int expr(const char **p);  /* prototype */

int factor(const char **p) {
    if (**p == '(') {
        (*p)++;
        int v = expr(p);
        if (**p != ')') {
            if (**p == '\0') err_end();
            else             err_tok(**p);
        }
        (*p)++;
        return v;
    }
    if (isdigit((unsigned char)**p)) {
        int v = **p - '0';
        (*p)++;
        return v;
    }
    if (**p == '\0') err_end();
    err_tok(**p);
    return 0; /* jamais atteint */
}

int term(const char **p) {
    int v = factor(p);
    while (**p == '*') {
        (*p)++;
        v *= factor(p);
    }
    return v;
}

int expr(const char **p) {
    int v = term(p);
    while (**p == '+') {
        (*p)++;
        v += term(p);
    }
    return v;
}

int main(int argc, char **argv) {
    if (argc != 2) return 0;
    const char *s = argv[1];
    int result = expr(&s);
    if (*s != '\0') {
        err_tok(*s);
    }
    printf("%d\n", result);
    return 0;
}
