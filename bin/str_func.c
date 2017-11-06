#include "../inc/str_func.h"
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>


char **str_split      (char *input, const char *delim, int *len) {

  char **out = NULL;
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

char *str_arr_join (char **input, const char *sep, int len) {

  // calculate output strings length
  int out_len = 0;
  for (int i = 0; i < len; i++) {
    out_len += strlen(input[i]);
  }
  out_len += strlen(sep) * (len-1);

  char *out = (char*) malloc(out_len + 1);
  if (out == NULL) return out;
  out[0] = '\0';

  for (int i = 0; i < len; i++) {
    strcat(out, input[i]);
    if (i < len-1) strcat(out, sep);
  }

  return out;

}

char  *str_filter_out (char *input, const char *filter) {

  int ws_count = 0;

  int str_len = (int) strlen(input);
  int filter_len = (int) strlen(filter);
  for (int i = 0; i < str_len; i++) {
    for (int j = 0; j < filter_len; j++) {
      if (input[i] == filter[j]) {
        ws_count++;
        break;
      } // END if
    } // END for j
  } // END for i

  char *out = (char*) malloc(str_len + 1 - ws_count);
  int cpy_count = 0;

  for (int i = 0; i < str_len; i++) {
    // fist check if current char is in filter
    int cpy = true;
    for (int j = 0; j < filter_len; j++) {

      if (input[i] == filter[j]) {
        cpy = false;
      }

    } // END for j

    // if not then copy it
    if (cpy) {
      out[cpy_count] = input[i];
      cpy_count++;
    }

  } // END for i

  return out;

}
