/* sh_env.h - Environment variable management */
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
 * see <https://www.gnu.org/licenses/>
 */

#ifndef SH_ENV_H
#define SH_ENV_H 1

/* initialize the environment from the parent process */
void sh_env_init(void);

/* gets the environment variable name */
char* sh_env_get(const char* name);

/* sets an environment variable */
int sh_env_set(const char* name, const char* value);

/* unsets an environment variable */
int sh_env_unset(const char* name);

/* prints all the environment variables */
void sh_env_print_all(void);

#endif

