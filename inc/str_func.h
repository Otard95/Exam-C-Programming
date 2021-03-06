#ifndef __STRING_FUNCTIONS_H__
#define __STRING_FUNCTIONS_H__

char **str_split       (char *input, const char *delim, int *len);
char  *str_arr_join    (char **input, const char *sep, int start, int end);
char  *str_filter_out  (char *input, const char *filter);
char  *cat_strings     (char *sep, int str_count, ...);
char  *crop_whitespace (char *str);

#endif // __STRING_FUNCTIONS_H__
