#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#include "sh_builtin.h"
#include "sh_configs.h"
#include "sh_exec.h"

int main(int argc, char* argv[]) {
	sh_load_configs();

	fprintf(stdout, "Welcome to Latbase shell!\n");
	fprintf(stdout, "You are currently running a PRE-RELEASE version of the program, so\n");
	fprintf(stdout, "feel free to contribute by adding new features, improvise come code\n");
	fprintf(stdout, "here and there, so don't hesitate to do so!\n");
	fprintf(stdout, "Licensed under the terms and conditions of the GNU General Public License\n");
	fprintf(stdout, "version 3.0\n");
	fprintf(stdout, "Copyright (C) 2026 Iurie Jurja\n");
	fprintf(stdout, "\n");

	while (true) {
		char* line = NULL;
		size_t len = 0;
		char* save_ptr = NULL;

		/* todo: set custom shell prompt, we'll find a way to do this */
		fprintf(stdout, "sh-pre# ");
		fflush(stdout);

		ssize_t read = getline(&line, &len, stdin);
		if (read == -1) break;

		if (read > 0 && line[read-1] == '\n') line[read-1] = '\0';
		if (line[0] == '\0') continue;

		char* argv[64] = {0};
		int i = 0;

		char* saveptr;
		char* token = strtok_r(line, " \t", &saveptr);

		while (token && i < 63) {
			argv[i++] = token;
			/* todo: execute other programs, not just the built-in commands */
			token = strtok_r(NULL, " \t", &saveptr);
		}
		argv[i] = NULL;

		sh_exec(i, argv);
	}

	return 0;
}

