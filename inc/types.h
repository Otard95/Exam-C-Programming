#ifndef __TYPES_H__
#define __TYPES_H__

typedef unsigned char BYTE;

typedef enum {
  FOLDER_NODE,
  STRING_NODE,
  INTEGER_NODE,
  UNKNOWN
} NODE_TYPE;

typedef enum {
  OK,
  NODE_NOT_FOLDER,
  NODE_NOT_INTEGER,
  NODE_NOT_STRING,
  NODE_ALREADY_EXISTS,
  NODE_NOT_FOUND,
  PATH_NOT_DIRECTORY,
  ALLOC_FAIL
} STATUS_CODE;

typedef union {
  int i;
  const char *c;
} StringInt;

#endif // __TYPES_H__
