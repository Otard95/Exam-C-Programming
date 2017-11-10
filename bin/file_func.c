#include "../inc/file_func.h"
#include "../inc/types.h"
#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>

STATUS_CODE read_file_to_str(char *buff, char *filename) {

  struct stat sBuffer;
  int iRc;

  iRc = stat(filename, &sBuffer);
  if (iRc == -1) { return FILE_NOT_FOUND; }

  FILE *fp = fopen(filename, "r");
  buff = (char*) malloc(sBuffer.st_size + 1);

  if (buff == NULL) { return ALLOC_FAIL; }

  if (fread(buff, 1, sBuffer.st_size, fp) != (size_t) sBuffer.st_size) {
    return FILE_READ_ERROR;
  }

  buff[sBuffer.st_size] = '\0';

  return OK;

}
