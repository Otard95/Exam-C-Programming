#ifndef __TREE_FUNCTIONS_H__
#define __TREE_FUNCTIONS_H__

#include "fof_node.h"
#include "types.h"

fofNode     *Traverse  (fofNode *root, char *path);
STATUS_CODE CreatePath (fofNode *root, char *path);

STATUS_CODE SetInt (fofNode *root, char *path, int   val);
STATUS_CODE SetStr (fofNode *root, char *path, char *val);

NODE_TYPE GetType (fofNode *root, char *path);
int   GetInt      (fofNode *root, char *path);
char *GetStr      (fofNode *root, char *path);

StringInt   GetValue (fofNode *root, char *path);
STATUS_CODE SetValue (fofNode *root, char *path, StringInt val);

void Enumerate (fofNode *root, char *path, void (*callback)(char *, StringInt ));

STATUS_CODE Delete (fofNode *root, char *path);

#endif // __TREE_FUNCTIONS_H__
