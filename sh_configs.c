/* sh_configs.c - The brains of the config loader function. */
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

#include "sh_configs.h"
#include "sh_env.h"

#include <stdio.h>

void sh_load_configs(void) {
	/* todo: load some sh-specific configuration files, e.g. from /etc or from the user's home directory */
	char* home = sh_env_get("HOME");

	/* we do NOT have a .shrc file in place yet, so this is a placeholder */
	/* i hope this does NOT fuck up the rest */
	if (home != NULL) {
		char shrc_path[512];
		snprintf(shrc_path, sizeof(shrc_path), "%s/.shrc", home);
	}
}

