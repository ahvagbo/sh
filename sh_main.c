/* sh_main.c - The main part of the shell. */
/* Copyright (C) 2026 Iurie Jurja */

/*
 * This file is part of Latbase Shell.
 *
 * Latbase Shell is free software: you can redistribute it and/or modify it under the terms of the GNU
 * General Public License as published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * Latbase Shell is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE. See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with Latbase Shell. If not,
 * see <https://www.gnu.org/licenses/>/
 */

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#include "sh_builtin.h"
#include "sh_configs.h"
#include "sh_exec.h"

int main(int argc, char* argv[]) {
	sh_load_configs();

	fprintf(stdout, "Latbase Shell, under construction\n");
	fprintf(stdout, "Copyright (C) 2026 Iurie Jurja\n\n");
	fprintf(stdout, "This program is free software: you can redistribute it and/or modify\n");
	fprintf(stdout, "it under the terms of the GNU General Public License as published by\n");
	fprintf(stdout, "the Free Software Foundation, either version 3 of the License, or\n");
	fprintf(stdout, "(at your option) any later version.\n\n");
	fprintf(stdout, "This program is distributed in the hope that it will be useful,\n");
	fprintf(stdout, "but WITHOUT ANY WARRANTY; without even the implied warranty of\n");
	fprintf(stdout, "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the\n");
	fprintf(stdout, "GNU General Public License for more details.\n\n");
	fprintf(stdout, "You should have received a copy of the GNU General Public License\n");
	fprintf(stdout, "along with this program. If not, see <https://www.gnu.org/licenses/>\n");
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

