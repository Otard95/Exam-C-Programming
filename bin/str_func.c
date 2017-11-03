#include "../inc/str_func.h"
#include <string.h>
#include <stdlib.h>

char **str_split      (char *input, const char *delim, int *len) {

  char **out;
  *len = 0;
  char *token;

   /* get the first token */
   token = strtok(input, delim);

   /* walk through other tokens */
  while( token != NULL ) {

    (*len)++;
    out = (char**) realloc(out, sizeof(char*) * (*len));
    if (out == NULL) return out;

    out[(*len)-1] = (char*) malloc(strlen(token)+1);
    strcpy(out[(*len)-1], token);

    token = strtok(NULL, delim);
  }

  return out;

}

char  *str_filter_out (char *input, const char filter);
