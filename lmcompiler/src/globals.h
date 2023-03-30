#include <argp.h>

#define MAX_FILE_SIZE 1000000

const char *argp_program_version = "lmcomp 0.1";
const char *argp_program_bug_address = "<admin@tomj.xyz>";

static char doc[] = 
	"LetterMark CLI Compiler\vReplace INPUT_FILE with - to read from STDIN";
static char args_doc[] = "INPUT_FILE OUTPUT_FILE";

static struct argp_option options[] = {
    {"config", 'c', "FILE", 0, "Explicit configuration file path"},
    {"quiet", 'q', 0, 0, "Suppress logging to STDOUT"},
    {0}
};
