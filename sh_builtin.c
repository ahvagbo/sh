/* sh_builtin.c - The brains of the built-in shell commands. */
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

#include "sh_builtin.h"
#include "sh_prompt.h"
#include "sh_env.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int sh_builtin_help(char* args[]) {
	fprintf(stdout, "All available commands in Latbase Shell:\n");

	for (int i = 0; i < sh_num_builtins(); i++) {
		fprintf(stdout, "%s\n", builtins[i]);
	}

	return 0;
}

int sh_builtin_cat(char* args[]) {
	return 0;
}

int sh_builtin_pwd(char* args[]) {
	char* current_dir = getcwd(NULL, 0);
	
	if (current_dir == NULL) {
		fprintf(stderr, "pwd: failed\n");
		return -1;
	}

	fprintf(stdout, "%s\n", current_dir);

	return 0;
}

int sh_builtin_cd(char* args[]) {
	if (chdir(args[1]) != 0) {
		fprintf(stderr, "cd: %s misspelled or not found\n", args[1]);
	}
	getcwd(workingdir, sizeof(workingdir) - 1);
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

int sh_builtin_export(char* args[]) {
	if (args[1] == NULL) {
		sh_env_print_all();
		return 0;
	}

	char* arg = args[1];
	char* equals = strchr(arg, '=');

	if (equals != NULL) {
		int var_len = equals - arg;
		char var_name[256];
		strncpy(var_name, arg, var_len);
		var_name[var_len] = '\0';

		char* var_value = equals + 1;
		sh_env_set(var_name, var_value);
		return 0;
	} else {
		return 0;
	}
}

int sh_builtin_unset(char* args[]) {
	if (args[1] == NULL) {
		fprintf(stderr, "unset: missing operand\n");
		return 1;
	}

	return sh_env_unset(args[1]);
}

int sh_builtin_env(char* args[]) {
	sh_env_print_all();
	return 0;
}

int sh_builtin_exit(char* args[]) {
	exit(0);
	return 0;
}

int (*builtin_commands[])(char* args[]) = {
	*sh_builtin_help,
	*sh_builtin_echo,
	*sh_builtin_cat,
	*sh_builtin_pwd,
	*sh_builtin_cd,
	*sh_builtin_export,
	*sh_builtin_unset,
	*sh_builtin_env,
	*sh_builtin_exit
};

char* builtins[] = {
	"help",
	"echo",
	"cat",
	"pwd",
	"cd",
	"export",
	"unset",
	"env",
	"exit"
};

int sh_num_builtins() {
	return sizeof(builtins) / sizeof(char*);
}

