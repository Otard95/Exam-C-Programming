#include "../inc/str_func.h"
#include <string.h>
#include <stdlib.h>

char **str_split      (char *input, const char delim, int *len);
char  *str_filter_out (char *input, const char filter);
