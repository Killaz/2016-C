#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define elif else if

char strCmp(char *s1, char *s2) {
	unsigned int len, i;
	if ((len = strlen(s1)) != strlen(s2))
		return 1;
	for (i = 0; i < len; i++)
		if (s1[i] != s2[i])
			return 1;
	return 0;
}

void read(char *where) {
	char c;
	int i = 0;
	while ((c = getchar()) != '\n') //13
		where[i++] = c;
	where[i] = 0;
}
int main(int argc, char *argv[]) {
	char command[50], s[120];
	int i;
	FILE *db;
	if ((db = fopen(argv[1], "rt")) == NULL)
		;
	while(1) {
		scanf("%s ", command);
		if (!strCmp(command, "find")) {
			read(s);
			printf("%s\n", s);
		} elif (!strCmp(command,"exit")) {
			break;
		}
	}	
	return 0;
}
