/* sh_builtin_pwd.c - "pwd" command implementation */
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
#include <stdio.h>
#include <unistd.h>

int sh_builtin_pwd(char* args[]) {
	char* current_dir = getcwd(NULL, 0);

	if (current_dir == NULL) {
		fprintf(stderr, "pwd: failed\n");
		return -1;
	}

	fprintf(stdout, "%s\n", current_dir);

	return 0;
}
