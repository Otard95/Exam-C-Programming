#ifndef __TREE_FUNCTIONS_H__
#define __TREE_FUNCTIONS_H__

#include "fof_node.h"
#include "types.h"

fofNode *Traverse (char *path);

STATUS_CODE SetInt (char *path, int   val);
STATUS_CODE SetStr (char *path, char *val);

NODE_TYPE GetType (char *path);
int   GetInt (char *path);
char *GetStr (char *path);

StringInt   GetValue (char *path);
STATUS_CODE SetValue (char *path, StringInt val);

void Enumerate (char *path, void (*callback)(char *path, StringInt val));

STATUS_CODE Delete (char *path);

#endif // __TREE_FUNCTIONS_H__
