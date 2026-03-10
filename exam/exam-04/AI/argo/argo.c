/* argo.c */
#include "argo.h"
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

static int E(int c)                    /* message d’erreur court */
{
	printf(c == EOF ?
	       "Unexpected end of input\n" :
	       "Unexpected token '%c'\n", c);
	return -1;
}

static int S(char **o, FILE *f)        /* lit une chaîne JSON */
{
	size_t l = 0; char *s = NULL; int c;
	while ((c = getc(f)) != EOF) {
		if (c == '"') {                    /* fin de chaîne */
			s = realloc(s, l + 1);
			s[l] = 0; *o = s; return 1;
		}
		if (c == '\\' && (c = getc(f)) == EOF)
			return free(s), E(EOF);       /* échappement inachevé */
		s = realloc(s, l + 1);
		s[l++] = c;                       /* copie caractère (évent. échappé) */
	}
	return free(s), E(EOF);               /* EOF avant le guillemet fermant */
}

static int J(json *d, FILE *f)         /* parseur récursif principal */
{
	int c = getc(f);
	if (c == EOF) return E(EOF);

	/* -------- STRING -------- */
	if (c == '"') {
		if (S(&d->string, f) < 0) return -1;
		d->type = STRING; return 1;
	}

	/* -------- INTEGER -------- */
	if (isdigit(c)) {
		int n = c - '0';
		while ((c = getc(f)) != EOF && isdigit(c))
			n = n * 10 + (c - '0');
		if (c != EOF) {                    /* vérifie séparateur après le nombre */
			if (c != ',' && c != '}') return E(c);
			ungetc(c, f);
		}
		d->type = INTEGER; d->integer = n; return 1;
	}

	/* -------- MAP / OBJET -------- */
	if (c == '{') {
		pair *a = NULL; size_t n = 0;
		for (;;) {
			c = getc(f);
			if (c == '}') {                 /* objet vide ou fin de liste */
				d->type = MAP; d->map.data = a; d->map.size = n; return 1;
			}
			if (c != '"') return free(a), E(c == EOF ? EOF : c);

			/* clé */
			char *k; if (S(&k, f) < 0) return free(a), -1;
			if ((c = getc(f)) != ':') return free(k), free(a), E(c == EOF ? EOF : c);

			/* valeur (récursion) */
			json v; if (J(&v, f) < 0) return free(k), free(a), -1;

			a = realloc(a, (n + 1) * sizeof *a);
			a[n++] = (pair){k, v};

			c = getc(f);
			if (c == ',') continue;        /* autre paire à venir */
			if (c == '}') {                /* fin d’objet */
				d->type = MAP; d->map.data = a; d->map.size = n; return 1;
			}
			return free(a), E(c == EOF ? EOF : c);
		}
	}
	return E(c);                          /* caractère de départ inconnu */
}

int argo(json *d, FILE *f)              /* point d’entrée officiel */
{
	int c;
	return J(d, f) < 0 ? -1 :
	       ((c = getc(f)) == EOF ? 1 : E(c));
}



/// main test

static void dump(FILE *o, const json *j)
{
	if (j->type == STRING) {
		fputc('"', o);
		for (const char *p = j->string; *p; ++p) {
			if (*p == '"' || *p == '\\') fputc('\\', o);
			fputc(*p, o);
		}
		fputc('"', o);
	} else if (j->type == INTEGER) {
		fprintf(o, "%d", j->integer);
	} else {                        /* MAP */
		fputc('{', o);
		for (size_t i = 0; i < j->map.size; ++i) {
			if (i) fputc(',', o);
			fputc('"', o);
			for (char *p = j->map.data[i].key; *p; ++p) {
				if (*p == '"' || *p == '\\') fputc('\\', o);
				fputc(*p, o);
			}
			fprintf(o, "\":");
			dump(o, &j->map.data[i].value);
		}
		fputc('}', o);
	}
}

int main(int ac, char **av)
{
	if (ac != 2) {
		fprintf(stderr, "usage: %s <file>\n", av[0]);
		return 1;
	}
	FILE *f = fopen(av[1], "r");
	if (!f) { perror(av[1]); return 1; }

	json root;
	if (argo(&root, f) == 1)        /* valide → ré-émission */
		dump(stdout, &root);

	fclose(f);
	return 0;
}