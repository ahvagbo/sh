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
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>

int sh_exec(int argc, char* argv[]) {
	int i;

	if (argv == NULL || argv[0] == NULL) {
		return 1;
	}

	for (i = 0; i < sh_num_builtins(); i++) {
		if (strcmp(argv[0], builtins[i]) == 0) {
			return (*builtin_commands[i])(argv);
		}
	}

	pid_t pid = fork();
	if (pid < 0) {
		perror("fork");
		return -1;
	}

	if (pid == 0) {
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		execvp(argv[0], argv);

		int err = errno;

		if (err == ENOENT) {
			fprintf(stderr, "%s: command not found\n", argv[0]);
		} else if (err == EACCES) {
			fprintf(stderr, "%s: permission denied\n", argv[0]);
		} else {
			fprintf(stderr, "%s: %s\n", argv[0], strerror(err));
		}

		_exit(127);
	}

	int status = 0;
	struct sigaction ignore_action, old_int_action, old_quit_action;
	memset(&ignore_action, 0, sizeof(ignore_action));
	ignore_action.sa_handler = SIG_IGN;
	sigemptyset(&ignore_action.sa_mask);
	ignore_action.sa_flags = 0;

	sigaction(SIGINT, &ignore_action, &old_int_action);
	sigaction(SIGQUIT, &ignore_action, &old_quit_action);

	while (true) {
		pid_t w = waitpid(pid, &status, 0);
		if (w == -1) {
			if (errno == EINTR) continue;
			perror("waitpid");
			status = -1;
			break;
		}
		break;
	}

	sigaction(SIGINT, &old_int_action, NULL);
	sigaction(SIGQUIT, &old_quit_action, NULL);

	if (status == -1) return -1;

	if (WIFEXITED(status)) {
		return WEXITSTATUS(status);
	} else if (WIFSIGNALED(status)) {
		int sig = WTERMSIG(status);
		return 128 + sig;
	}

	return status;
}

