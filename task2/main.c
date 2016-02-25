#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define elif else if

typedef struct hum {
	char name[30], tel[16];
	char sname[30];
};

typedef struct vector {
	struct hum *m;
	int n, mx;
};

void vecInit(struct vector *vec) {
	vec->m = (struct hum *) malloc(4 * sizeof(struct hum));
	vec->n = 0, vec->mx = 4;
}

void vecAdd(struct hum h, struct vector *vec) {
	struct hum *tmp;
	int i;
	if (vec->n + 1 == vec->mx) {
		if ((tmp = (struct hum *) malloc(vec->mx * 2 * sizeof(struct hum))) == NULL) {
			printf("\nFATAL ERROR OF MEMORY ADDITION\n");
			free(vec->m);
			exit(1);
		}
		for (i = 0; i < vec->n; i++)
			tmp[i] = vec->m[i];
		free(vec->m);
		vec->m = tmp;
		vec->mx *= 2;
	}
	vec->m[vec->n++] = h;
}

char vecDel(struct vector *vec, int id) {
	if (id < 0 || id > vec->mx)
		return 0;
	vec->m[id].name[0] = 0;
	vec->m[id].tel[0] = 0;
	return 1;
}

void printVec(struct vector vec) {                //debug stuff
	int i;
	fprintf(stderr, "Telephone book contains:\n");
	for (i = 0; i < vec.n; i++)
		if (vec.m[i].name[0] != 0)
			fprintf(stderr, "%3d: %s %s\n", i, vec.m[i].name, vec.m[i].tel);
	fprintf(stderr, "\n");
}

void saveVec(struct vector *vec, FILE *out) {
	int i;
	for (i = 0; i < vec->n; i++)
		if (vec->m[i].name[0] != 0)
			fprintf(out, "%s %s\n", vec->m[i].name, vec->m[i].tel);
}

char strCmp(char *s1, char *s2) {
	unsigned int len, i;
	if ((len = strlen(s1)) != strlen(s2))
		return 1;
	for (i = 0; i < len; i++)
		if (s1[i] != s2[i])
			return 1;
	return 0;
}

void strCpy(char *where, char *from) {
	int i = 0;
	do {
		where[i] = from[i];
	} while (from[i++] != 0);
}

void bigToSmall(char *s) {
	while (*s != 0) {
		if (*s >= 'A' && *s <= 'Z')
			*s -= 'A' - 'a';
		s++;
	}
}

void read(char *where) {
	char c;
	int i = 0;
	while ((c = getchar()) != '\n') //13
		if (c != ' ' && c != '(' && c != ')' && c != '-')
			where[i++] = c;
	where[i] = 0;
}

char from8to7(char *s) {
	int i = strlen(s);
	if (s[0] != '8')
		if ((s[0] >= '0' && s[0] <= '9') || s[0] == '+')
			return 0;
		else
			return -1;
	s[i + 1] = 0;
	for (; i > 0; i--)
			s[i] = s[i - 1];
	s[0] = '+', s[1] = '7';
	return 1;
}

void searchTel(char *s, struct vector *v) {
	int i;
	for (i = 0; i < v->n; i++)
		if (!strCmp(v->m[i].tel, s))
			printf("%d %s %s\n", i, v->m[i].name, v->m[i].tel);
	printf("\n");
}

void searchName(char *s, struct vector *v) {
	int i, j, k, lenS, len;
	char flag;
	lenS = strlen(s);
	for (i = 0; i < v->n; i++) {
		len = strlen(v->m[i].sname);
		flag = 0;
		for (j = 0; j <= len - lenS; j++) {
			if (flag)
				break;
			k = 0;
			while (k < lenS && v->m[i].sname[j + k] == s[k])
				k++;
			if (k == lenS) {
				printf("%d %s %s\n", i, v->m[i].name, v->m[i].tel), flag = 1;
			}
		}
	}
}


int main(int argc, char *argv[]) {
	int i;
	char command[50], s[80], last = 0;
	struct hum h;
	struct vector book;
	FILE *db;
	vecInit(&book);
	if (argc == 1) {
#ifndef DEBUG
		return 1;
#else
		argc = 2;
		argv = (char **) realloc(argv, sizeof(argv) + sizeof(char **));
		argv[1] = (char *) realloc(argv[1], sizeof("test.book"));
		strCpy(argv[1], "test.book");
#endif
	}
	if ((db = fopen(argv[1], "rt")) != NULL) {
		while(1) {
			if ((i = fscanf(db, "%s %s", h.name, h.tel)) != 2) // "name tel" scan
				break;
			strCpy(h.sname, h.name);
			bigToSmall(h.sname);
			vecAdd(h, &book);
		}
		last = 'r';
	}
	while(1) {
		fprintf(stderr, "\n@Book: ");
		scanf("%s", command);
		bigToSmall(command);
		if (!strCmp(command, "find")) {
			read(s);
			if (!strCmp(s, "*"))
				printVec(book);
			i = from8to7(s);
			if (i == -1) {                             // part of name
				bigToSmall(s);
				searchName(s, &book);
			} else                                     // tel-number
				searchTel(s, &book);
		} elif (!strCmp(command, "create")) {
			scanf("%s", h.name);
			strCpy(h.sname, h.name);
			bigToSmall(h.sname);
			read(h.tel);
			from8to7(h.tel);                           // RLY needed?
			vecAdd(h, &book);
			if (last != 'w' && last != 'W')
				if (last == 0)
					db = fopen(argv[1], "wt"), last = 'w';
				else {
					fclose(db);
					db = fopen(argv[1], "w+"), last = 'W';
				}
			fprintf(db, "%s %s\n", h.name, h.tel);
		} elif (!strCmp(command, "delete")) {
			scanf("%d", &i);
			vecDel(&book, i);
			if (last != 0) {
				freopen(argv[1], "wt", db);
				saveVec(&book, db);
				last = 'w';
			}
		} elif (!strCmp(command, "change")) {
			scanf("%d %s", &i, s);
			read(h.name);                              // name or tel - tmp (name > tel)
			if (!strCmp(s, "name")) {                  // unsafe
				strCpy(book.m[i].name, h.name);
				strCpy(book.m[i].sname, h.name);
				bigToSmall(book.m[i].sname);
			} elif (!strCmp(s, "number")) {
				strCpy(book.m[i].tel, h.name);
			} else
				fprintf(stderr, "Error: %s is not \"name\" of \"number\"\n", s);
			if (last != 0) {
				freopen(argv[1], "wt", db);
				saveVec(&book, db);
				last = 'w';
			} else
				fprintf(stderr, "\nFATAL ERROR: something changed, without file of saving => no people in book\n"
				                "Continue working, ignoring writing out of memory\n");
		} elif (!strCmp(command, "help")) {
			fprintf(stderr, "@Help (with debug info):\n  \"create <name> <tel. number>\" - add person to base\n"
				   "  \"find <number>\" or \"find <part of name>\" - get list of found persons\n"
				   "  \"find *\" - print all info from database\n"
				   "  \"change <id> name <new name>\" or \"change <id> number <new tel. number>\" - change existing person's info\n"
				   "  \"delete <id>\" - delete person from base\n"
				   "  \"exit\" - quit application (information is saved after every action)\n");
		} elif (!strCmp(command, "exit")) {
			break;
		} else
			fprintf(stderr, "Error: %s - not a command\n", command);
	}
	return 0;
}
