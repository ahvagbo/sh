/* sh_builtin_cd.c - "cd" command implementation */
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
#include <stdio.h>
#include <unistd.h>

int sh_builtin_cd(char* args[]) {
    if (chdir(args[1]) != 0) {
        fprintf(stderr, "cd: %s misspelled or not found\n", args[1]);
    }
    getcwd(workingdir, sizeof(workingdir) - 1);
    return 0;
}
