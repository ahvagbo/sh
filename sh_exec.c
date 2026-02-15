/* sh_exec.c - The brains of the sh_exec function. */
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

#include "sh_exec.h"

#include <stdio.h>
#include <stddef.h>
#include <string.h>

int sh_exec(int argc, char* argv[]) {
	int i;

	if (argv[0] == NULL) {
		return 1;
	}

	for (i = 0; i < sh_num_builtins(); i++) {
		if (strcmp(argv[0], builtins[i]) == 0) {
			return (*builtin_commands[i])(argv);
		}
	}

	return 0;
}

