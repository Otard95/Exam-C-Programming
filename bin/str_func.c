#include "../inc/str_func.h"
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdarg.h>


char **str_split (char *input, const char *delim, int *len) {

  char **out = NULL;
  char **last = NULL;
  *len = 0;
  char *token;

  /* get the first token */
  token = strtok(input, delim);

   /* walk through other tokens */
  while( token != NULL ) {

    (*len)++;
    last = out;
    out = (char**) realloc(out, sizeof(char*) * (*len));
    if (out == NULL) { // is realloc failed
      // Cleanup using **last.
      for (int i = 0; i < (*len)-1; i++) {
        free(last[i]);
      }
      free(last);
      return out;
    }

    out[(*len)-1] = (char*) malloc(strlen(token)+1);
    strcpy(out[(*len)-1], token);

    token = strtok(NULL, delim);
  }

  return out;

}

char *str_arr_join (char **input, const char *sep, int start, int end) {

  // calculate output strings length
  int out_len = 0;
  for (int i = start; i < end; i++) {
    out_len += strlen(input[i]);
  }
  out_len += strlen(sep) * (end - start - 1);

  char *out = (char*) malloc(out_len + 1);
  if (out == NULL) return out;
  out[0] = '\0';

  for (int i = start; i < end; i++) {
    strcat(out, input[i]);
    if (i < end-1) strcat(out, sep);
  }

  return out;

}

char *str_filter_out (char *input, const char *filter) {

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

char *cat_strings (char *sep, int str_count, ...) {

    va_list valist;
    int i;
    char *curr_str;

    int len = 0;
    char *out;
    char *last = NULL;

    /* initialize valist for 'str_count' number of arguments */
    va_start(valist, str_count);

    /* access all the arguments assigned to valist */
    for (i = 0; i < str_count; i++) {

      // get next string and update 'len'
      curr_str = va_arg(valist, char*);
      len += strlen(curr_str);
      if (i == 0 && sep != NULL) {
        /* if not first str && 'sep' is specified */
        len += strlen(sep);
      }

      last = out;
      out = (char*) realloc(out, len +1);
      if (out == NULL) {
        // Cleanup
        if (last != NULL) free(last);
        break;
      }

      if (i == 0 && sep != NULL) { strcat(out, sep); }
      strcat(out, curr_str);

    }

    /* clean memory reserved for valist */
    va_end(valist);

    return out;

}
