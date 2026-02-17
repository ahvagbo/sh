/* sh_prompt.c - Shell prompt management implementation */
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

#include "sh_prompt.h"

#include <sys/types.h>
#include <pwd.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

static char username[256] = "";
static char hostname[256] = "";
static char workingdir[256] = "";
static uid_t current_uid = 0;

void sh_prompt_init(void) {
	current_uid = getuid();
	struct passwd *pwd = getpwuid(current_uid);

	/* we need the user name */
	if (pwd != NULL) {
		strncpy(username, pwd->pw_name, sizeof(username) - 1);
		username[sizeof(username) - 1] = '\0';
	} else {
		snprintf(username, sizeof(username), "%d", current_uid);
	}

	/* and now we retrieve the hostname */
	if (gethostname(hostname, sizeof(hostname) - 1) != 0) {
		strncpy(hostname, "localhost", sizeof(hostname) - 1);
	}
	hostname[sizeof(hostname) - 1] = '\0';
	getcwd(workingdir, sizeof(workingdir) - 1);

	fprintf(stdout, "[ %s@%s:%s ]", username, hostname, workingdir);
	if (current_uid == 0) fprintf(stdout, "# ");
	else fprintf(stdout, "$ ");
}

