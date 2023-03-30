#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <argp.h>
#include <hpdf.h>

#include "globals.h"
#include "../../liblm/include/liblm.h"

typedef struct arguments
{
	char *np_args[2];
	char *config_file;
	int quiet;
} t_args;


static error_t parse_opt(int key, char *arg, struct argp_state *state)
{
	t_args *input = state->input;

	switch (key)
	{
		case 'c':
			input->config_file = arg;
			break;
		case 'q':
			input->quiet = 1;
			break;
		case ARGP_KEY_ARG:	// Non-option argument
			if (state->arg_num >=2)
				argp_usage(state);	// Too many arguments
			input->np_args[state->arg_num] = arg;	// Sets the input strings
			break;
		case ARGP_KEY_END:
			if (state->arg_num < 2)
				argp_usage(state);	// Not enough arguments
			break;
		default:
			return ARGP_ERR_UNKNOWN;
	}

	return 0;
}

static struct argp argparse = {options, parse_opt, args_doc, doc};

int allocate_content_memory(char **content)
{
	*content = (char *)malloc(MAX_FILE_SIZE + 1);
	if (*content == NULL)
	{
		perror("Error allocating memory for file content");
		return -1;
	}
	else {
		return 0;
	}
}

int read_file(const char *fn, char **content)
{
	FILE *file = fopen(fn, "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    if (allocate_content_memory(content) == -1) {
        fclose(file);
        return 2;
    }

    size_t bytes_read = fread(*content, 1, file_size, file);
    if (bytes_read != file_size) {
        perror("Error reading file content");
        fclose(file);
        return 3;
    }

    (*content)[file_size] = '\0';
    fclose(file);
    return 0;
}

int main(int argc, char **argv)
{
	// Default state
	t_args args;
	args.quiet = 0;
	args.config_file = NULL;

	argp_parse(&argparse, argc, argv, 0, 0, &args);

	char *content;
	printf("%s", args.np_args[0]);
	if (strncmp(args.np_args[0], "-", 1) == 0)
	{
		if (allocate_content_memory(&content) == -1)
			return 1;
		// Read from stdin
		if (read(STDIN_FILENO, content, MAX_FILE_SIZE) == -1)
		{
			perror("Error reading from STDIN");
			return 1;
		}
	}
	else
	{
		read_file(args.np_args[0], &content);
	}

    lm_compile(content, args.np_args[1]);

	return 0;
}
