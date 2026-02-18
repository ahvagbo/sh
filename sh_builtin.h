/* sh_builtin.h - The definitions for the built-in shell commands. */
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

#ifndef SH_BUILTIN_H
#define SH_BUILTIN_H 1

/* we obviously need ts */
int sh_builtin_help(char* args[]);

int sh_builtin_echo(char* args[]);

/* file utilities, i guess */
int sh_builtin_cat(char* args[]);
int sh_builtin_pwd(char* args[]);
int sh_builtin_cd(char* args[]);

int sh_builtin_exit(char* args[]);

/* environment variable specific commands */
int sh_builtin_export(char* args[]);
int sh_builtin_unset(char* args[]);
int sh_builtin_env(char* args[]);

extern int (*builtin_commands[])(char* args[]);
extern char* builtins[];

int sh_num_builtins();

#endif

