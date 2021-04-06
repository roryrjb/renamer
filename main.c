#include <getopt.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>

static char *filename;

static int insert_filename() {
	if (filename != NULL) {
		rl_insert_text(filename);
		rl_startup_hook = NULL;
	}

	return 0;
}

int main(int argc, char **argv) {
	while (optind < argc) {
		filename = argv[optind++];
		char *prompt = "> ";
		rl_startup_hook = insert_filename;
		char *name = readline(prompt);

		if (name == NULL) {
			printf("\n");
			continue;
		}

		if (strcmp(filename, name) != 0) {
			int res = rename(filename, name);

			if (res == -1) {
				perror("rename");
				exit(EXIT_FAILURE);
			}

			printf("Renamed '%s' to '%s'\n", filename, name);
		}

		free(name);
	}
}
