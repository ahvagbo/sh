#include "sh_builtin.h"

#include <stdio.h>

int sh_builtin_uname(char* args[]) {
	/* this is a placeholder */
	fprintf(stdout, "Linux\n");
	return 0;
}

int sh_builtin_cat(char* args[]) {
	return 0;
}

int sh_builtin_echo(char* args[]) {
	size_t i;
	size_t len = 0;
	while (args[len]) len++;

	bool first = true;
	for (i = 1; i < len; i++) {
		if (!first) fprintf(stdout, " ");
		fprintf(stdout, "%s", args[i]);
		first = false;
	}

	fprintf(stdout, "\n");

	return 0;
}

int (*builtin_commands[])(char* args[]) = {
	*sh_builtin_echo,
	*sh_builtin_cat,
	*sh_builtin_uname
};

char* builtins[] = {
	"echo",
	"cat",
	"uname"
};

int sh_num_builtins() {
	return sizeof(builtins) / sizeof(char*);
}

