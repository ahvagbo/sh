/* sh_env.c - Environment variable management implementation */
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

#include "sh_env.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ENV_VARS 512

typedef struct {
	char *name;
	char* value;
} env_var_t;

static env_var_t env_vars[MAX_ENV_VARS];
static int env_count = 0;

extern char **environ;

void sh_env_init(void) {
	env_count = 0;

	if (environ) {
		for (int i = 0; environ[i] != NULL && env_count < MAX_ENV_VARS; i++) {
			char* env_str = environ[i];
			char* equals = strchr(env_str, '=');

			if (equals != NULL) {
				int name_len = equals - env_str;
				char* name = malloc(name_len + 1);
				strncpy(name, env_str, name_len);
				name[name_len] = '\0';

				char* value = malloc(strlen(equals + 1) + 1);
				strcpy(value, equals + 1);

				env_vars[env_count].name = name;
				env_vars[env_count].value = value;
				env_count++;
			}
		}
	}

	/* let's make sure SHLVL is set */
	char* shlvl = sh_env_get("SHLVL");
	if (shlvl == NULL) {
		sh_env_set("SHLVL", "1");
	} else {
		int level = atoi(shlvl) + 1;
		char level_str[16];
		snprintf(level_str, sizeof(level_str), "%d", level);
		sh_env_set("SHLVL", level_str);
	}
}

char* sh_env_get(const char* name) {
	if (name == NULL) return NULL;

	for (int i = 0; i < env_count; i++) {
		if (strcmp(env_vars[i].name, name) == 0) {
			return env_vars[i].value;
		}
	}

	return NULL;
}

int sh_env_set(const char* name, const char* value) {
	if (name == NULL || value == NULL) return -1;

	for (int i = 0; i < env_count; i++) {
		if (strcmp(env_vars[i].name, name) == 0) {
			free(env_vars[i].value);
			env_vars[i].value = malloc(strlen(value) + 1);
			strcpy(env_vars[i].value, value);
			return 0;
		}
	}

	if (env_count >= MAX_ENV_VARS) {
		fprintf(stderr, "error: environment storage full\n");
		return -1;
	}

	env_vars[env_count].name = malloc(strlen(name) + 1);
	strcpy(env_vars[env_count].name, name);
	env_vars[env_count].value = malloc(strlen(value) + 1);
	strcpy(env_vars[env_count].value, value);
	env_count++;

	return 0;
}

int sh_env_unset(const char* name) {
	if (name == NULL) return -1;

	for (int i = 0; i < env_count; i++) {
		if (strcmp(env_vars[i].name, name) == 0) {
			free(env_vars[i].name);
			free(env_vars[i].value);

			for (int j = i; j < env_count - 1; j++) {
				env_vars[j] = env_vars[j + 1];
			}

			env_count--;
			return 0;
		}
	}

	return -1;
}

void sh_env_print_all(void) {
	for (int i = 0; i < env_count; i++) {
		fprintf(stdout, "%s=%s\n", env_vars[i].name, env_vars[i].value);
	}
}

