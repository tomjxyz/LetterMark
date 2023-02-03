#include <stdio.h>
#include <argp.h>

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

int main(int argc, char **argv)
{
	// Default state
	t_args args;
	args.quiet = 0;
	args.config_file = NULL;

	argp_parse(&argparse, argc, argv, 0, 0, &args);

    hello_world();

	return 0;
}
