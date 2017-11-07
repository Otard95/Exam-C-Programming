#ifndef __TREE_FUNCTIONS_H__
#define __TREE_FUNCTIONS_H__

#include "fof_node.h"
#include "types.h"

fofNode     *Traverse  (fofNode *, char *);
STATUS_CODE CreatePath (fofNode *, char *);

STATUS_CODE SetInt (fofNode *, char *, int);
STATUS_CODE SetStr (fofNode *, char *, char *);

NODE_TYPE GetType (fofNode *, char *, STATUS_CODE *);
int   GetInt      (fofNode *, char *, STATUS_CODE *);
char *GetStr      (fofNode *, char *, STATUS_CODE *);

StringInt   GetValue (fofNode *, char *, STATUS_CODE *);
STATUS_CODE SetValue (fofNode *, char *, StringInt);

void Enumerate (fofNode *, char *, void (*callback)(char *, StringInt ));

STATUS_CODE Delete (fofNode *, char *);

#endif // __TREE_FUNCTIONS_H__
