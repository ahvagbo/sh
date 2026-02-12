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

