#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define elif else if

struct string {
	char *s;
	int n, mx;
};

struct hum {
	int id;
	struct string name, sname, tel, stel;
};

struct vector {
	struct hum *m;
	int n, mx;
};

void humSwap(struct hum *a, struct hum *b) {
	struct hum c = *a;
	*a = *b;
	*b = c;
}

char strCmp(char *s1, char *s2) {
	unsigned int len, i;
	if ((len = strlen(s1)) != strlen(s2))
		return 0;
	for (i = 0; i < len; i++)
		if (s1[i] != s2[i])
			return 0;
	return 1;
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

void stringInit(struct string *str) {
	str->s = (char *) malloc(1 * sizeof(char));
	str->s[0] = 0;
	str->n = 0, str->mx = 1;
}

void vecInit(struct vector *vec) {
	vec->m = (struct hum *) malloc(1 * sizeof(struct hum));
	vec->n = 0, vec->mx = 1;
}

void humInit(struct hum *h) {
	stringInit(&h->name);
	stringInit(&h->sname);
	stringInit(&h->tel);
	stringInit(&h->stel);
	h->id = -1;
}

void stringClose(struct string *str) {
	if (str->s == NULL)
		return;
	free(str->s);
	str->s = NULL;
	str->n = str->mx = 0;
}

void humClose(struct hum *h) {
	if (h == NULL)
		return;
	stringClose(&h->name);
	stringClose(&h->name);
	stringClose(&h->name);
	stringClose(&h->name);
	h->id = -1;
}

void vecClose(struct vector *vec) {
	int i;
	if(vec == NULL)
		return;
	for (i = 0; i < vec->n; i++)
		humClose(&vec->m[i]);
	free(vec->m);
	vec->m = NULL;
	vec->n = vec->mx = 0;
}

void stringCopy(struct string *where, struct string *from) {
	if (from == NULL)
		return;
	stringClose(where);
	where->s = (char *) malloc(from->mx * sizeof(char) + 1);
	strCpy(where->s, from->s);
	where->n = from->n;
	where->mx = from->mx;
}

void stringAdd(char c, struct string *str) {
	char *tmp;
	int i;
	if (str == NULL)
		return;
	if (str->n + 1 == str->mx) {
		if ((tmp = (char *) malloc(str->mx * 2 * sizeof(char *))) == NULL) {
			printf("\nFATAL ERROR OF MEMORY ADDITION (stringAdd)\n");
			free(str->s);
			exit(1);
		}
		for (i = 0; i < str->n; i++)
			tmp[i] = str->s[i];
		free(str->s);
		str->s = tmp;
		str->mx *= 2;
	}
	str->s[str->n++] = c;
	str->s[str->n] = 0;
}

void vecAdd(struct hum h, struct vector *vec) {
	struct hum *tmp;
	int i;
	if (vec == NULL)
		return;
	if (vec->n == vec->mx) {
		if ((tmp = (struct hum *) malloc(vec->mx * 2 * sizeof(struct hum))) == NULL) {
			printf("\nFATAL ERROR OF MEMORY ADDITION (vecAdd)\n");
			free(vec->m);
			exit(1);
		}
		for (i = 0; i < vec->n; i++)
			tmp[i] = vec->m[i];
		free(vec->m);
		vec->m = tmp;
		vec->mx *= 2;
	}
	vec->m[vec->n].name.s = vec->m[vec->n].sname.s = vec->m[vec->n].tel.s = NULL;
	stringCopy(&vec->m[vec->n].name, &h.name);
	stringCopy(&vec->m[vec->n].sname, &h.sname);
	stringCopy(&vec->m[vec->n].tel, &h.tel);
	stringCopy(&vec->m[vec->n].stel, &h.stel);
	vec->m[vec->n].id = h.id;
	vec->n++;
}

void stringClear(struct string *str) {
	if (str == NULL)
		return;
	stringClose(str);
	stringInit(str);
}

char vecDel(int id, struct vector *vec) {
	int i;
	char flag = 0;
	struct hum *tmp;
	if (id < 0 || id > vec->mx)
		return 0;
	for (i = 0; i < vec->n; i++)
		if (vec->m[i].id == id) {
			flag = 1;
			break;
		}
	if (!flag)
		return 0;
	vec->n--;
	humSwap(&vec->m[i], &vec->m[vec->n]);
	stringClose(&vec->m[vec->n].name);
	stringClose(&vec->m[vec->n].sname);
	stringClose(&vec->m[vec->n].tel);
	stringClose(&vec->m[vec->n].stel);
	if (vec->n <= vec->mx / 4) {
		if ((tmp = (struct hum *) malloc(vec->mx / 2 * sizeof(struct hum))) == NULL) {
			printf("\nFATAL ERROR OF MEMORY ADDITION (vecDel)\n");
			free(vec->m);
			exit(1);
		}
		for (i = 0; i < vec->n; i++)
			tmp[i] = vec->m[i];
		free(vec->m);
		vec->m = tmp;
		vec->mx /= 2;
	}
	return 1;
}

void vecClear(struct vector *vec) {
	vecClose(vec);
	vecInit(vec);
}

char vecChange(int id, struct hum h, int what, struct vector *vec) { // what = {1 - name, 2 - tel, 3 - both
	int i;
	char flag = 0;
	for (i = 0; i < vec->n; i++)
		if (vec->m[i].id == id) {
			flag = 1;
			break;
		}
	if (!flag)
		return 0;
	if (what & 1) {
		stringCopy(&vec->m[i].name, &h.name);
		stringCopy(&vec->m[i].sname, &h.name);
		bigToSmall(vec->m[i].sname.s);
	}
	if ((what >> 1) & 1) {
		stringCopy(&vec->m[i].tel, &h.tel);
		stringCopy(&vec->m[i].stel, &h.stel);
	}
	return 1;
}

void printVec(struct vector vec) {                //debug stuff
	int i;
	fprintf(stderr, "Telephone book contains (%d of %d):\n", vec.n, vec.mx);
	for (i = 0; i < vec.n; i++) {
		fprintf(stderr, "%3d: %s (%s) %s (%s)\n", vec.m[i].id, vec.m[i].name.s, vec.m[i].sname.s, vec.m[i].tel.s, vec.m[i].stel.s);
//		fprintf(stderr, "\b   ---   (%d of %d)\n", vec.m[i].name.n, vec.m[i].name.mx);
	}
	fprintf(stderr, "\n");
	fflush(stderr);
}

void saveVec(struct vector *vec, FILE *out) {
	int i;
	for (i = 0; i < vec->n; i++)
		fprintf(out, "%s %s\n", vec->m[i].name.s, vec->m[i].tel.s);
	fflush(out);
}

char stringScan(struct string *where) {
	char c;
	stringClear(where);
	while ((c = getchar()) == ' ' || c == '\n')
		if (c == '\n')
			return 0;
	if (c != -1)
		stringAdd(c, where);
	else
		return 0;
	while ((c = getchar()) != ' ' && c != -1 && c != '\n')
		stringAdd(c, where);
	return where->n != 0;
}

char stringfScan(struct string *where, FILE *f) {
	char c;
	stringClear(where);
	while ((c = fgetc(f)) != ' ' && c != -1 && c != '\n')
		stringAdd(c, where);
	return where->n != 0;
}

char read(struct string *where1, struct string *where2) {
	char c;
	stringClear(where1);
	stringClear(where2);
	while ((c = getchar()) == ' ' || c == '\n')
		if (c == '\n')
			return 0;
	if (c != -1) {
		stringAdd(c, where1);
		if (c != ' ' && c != '(' && c != ')' && c != '-' && c != '+')
			stringAdd(c, where2);
	} else
		return 0;
	while ((c = getchar()) != '\n' && c != -1) {
		stringAdd(c, where1);
		if (c != ' ' && c != '(' && c != ')' && c != '-' && c != '+')
			stringAdd(c, where2);
	}
	return where1->n != 0;
}

char readf(struct string *where1, struct string *where2, FILE *f) {
	char c;
	stringClear(where1);
	stringClear(where2);
	while ((c = fgetc(f)) == ' ' || c == '\n')
		if (c == '\n')
			return 0;
	if (c != -1) {
		stringAdd(c, where1);
		if (c != ' ' && c != '(' && c != ')' && c != '-' && c != '+')
			stringAdd(c, where2);
	} else
		return 0;
	while ((c = fgetc(f)) != '\n') {
		stringAdd(c, where1);
		if (c != ' ' && c != '(' && c != ')' && c != '-' && c != '+')
			stringAdd(c, where2);
	}
	return where1->n != 0;
}

char from8to7(char *s) {           // Changed meaning
//	int i = strlen(s);
	if (s[0] != '8') {
		if ((s[0] >= '0' && s[0] <= '9') || s[0] == '+')
			return 0;
		else
			return -1;
	}
/*	s[i + 1] = 0;
	for (; i > 0; i--)
			s[i] = s[i - 1];
	s[0] = '+', s[1] = '7';*/
	return 1;
}

void searchTel(char *s, struct vector *v) {
	int i;
	for (i = 0; i < v->n; i++)
		if (strCmp(v->m[i].stel.s, s))
			printf("%d %s %s\n", v->m[i].id, v->m[i].name.s, v->m[i].tel.s);
	printf("\n");
	fflush(stdout);
}

void searchName(char *s, struct vector *v) {
	int i, j, k, lenS, len;
	char flag;
	lenS = strlen(s);
	for (i = 0; i < v->n; i++) {
		len = strlen(v->m[i].sname.s);
		flag = 0;
		for (j = 0; j <= len - lenS; j++) {
			if (flag)
				break;
			k = 0;
			while (k < lenS && v->m[i].sname.s[j + k] == s[k])
				k++;
			if (k == lenS) {
				printf("%d %s %s\n", v->m[i].id, v->m[i].name.s, v->m[i].tel.s), flag = 1;
			}
		}
	}
	fflush(stdout);
}


int main(int argc, char *argv[]) {
	int i, nowId = 0;
	char command[50], last = 0;
	struct string s;
	struct hum h;
	struct vector book;
	FILE *db;
	vecInit(&book);
	stringInit(&s);
	humInit(&h);
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
			if (!(stringfScan(&h.name, db) && readf(&h.tel, &h.stel, db)))
				break;
			stringCopy(&h.sname, &h.name);
			bigToSmall(h.sname.s);
			h.id = nowId++;
			vecAdd(h, &book);
		}
		last = 'r';
	}
	while(1) {
		fprintf(stderr, "\n@Book: ");
		scanf("%s", command);
		bigToSmall(command);
		if (strCmp(command, "find")) {
			read(&h.tel, &h.stel);                     // name or number
			if (strCmp(h.tel.s, "*"))
				printVec(book);
			i = from8to7(h.tel.s);
			from8to7(h.stel.s);
			if (i == -1) {                             // part of name
				bigToSmall(h.tel.s);
				searchName(h.tel.s, &book);
			} else                                     // tel-number
				searchTel(h.stel.s, &book);
		} elif (strCmp(command, "create")) {
			stringScan(&h.name);
			stringCopy(&h.sname, &h.name);
			bigToSmall(h.sname.s);
			read(&h.tel, &h.stel);
			h.id = nowId++;
			from8to7(h.tel.s);                         // RLY needed?
			vecAdd(h, &book);
			if (last != 'w' && last != 'W') {
				if (last == 0)
					db = fopen(argv[1], "wt"), last = 'w';
				else {
					fclose(db);
					db = fopen(argv[1], "w+"), last = 'W';
				}
			}
			fprintf(db, "%s %s\n", h.name.s, h.tel.s);
		} elif (strCmp(command, "delete")) {
			scanf("%d", &i);
			vecDel(i, &book);
#ifdef DEBUG
			if (i == -1)
				vecClear(&book);
#endif
			if (last != 0) {
				freopen(argv[1], "wt", db);
				saveVec(&book, db);
				last = 'w';
			}
		} elif (strCmp(command, "change")) {
			scanf("%d", &i);
			stringScan(&s);
			if (strCmp(s.s, "name")) {                  // unsafe
				stringScan(&h.name);
				vecChange(i, h, 1, &book);
			} elif (strCmp(s.s, "number")) {
				read(&h.tel, &h.stel);
				vecChange(i, h, 2, &book);
			} elif (strCmp(s.s, "both")) {
				stringScan(&h.name);
				read(&h.tel, &h.stel);
				vecChange(i, h, 3, &book);
			} else
				fprintf(stderr, "Error: %s is not \"name\", \"number\" or \"both\"\n", s.s);
			if (last != 0) {
				freopen(argv[1], "wt", db);
				saveVec(&book, db);
				last = 'w';
			} else
				fprintf(stderr, "\nFATAL ERROR: something changed, without file of saving => no people in book\n"
				                "Continue working, ignoring writing out of memory\n");
		} elif (strCmp(command, "help")) {
			fprintf(stderr, "@Help (with debug info):\n  \"create <name> <tel. number>\" - add person to base\n"
				   "  \"find <number>\" or \"find <part of name>\" - get list of found persons\n"
				   "  \"find *\" - print all info from database\n"
				   "  \"change <id> name <new name>\", \"change <id> number <new tel. number>\""
				   " or \"change <id> both <new name> <new tel. number>\" - change existing person's info\n"
				   "  \"delete <id>\" - delete person from base\n"
				   "  \"exit\" - quit application (information is saved after every action)\n");
		} elif (strCmp(command, "exit")) {
			break;
		} else
			fprintf(stderr, "Error: %s - not a command\n", command);
	}
	vecClose(&book);
	return 0;
}
