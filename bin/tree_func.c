#include "../inc/tree_func.h"
#include "../inc/fof_node.h"
#include "../inc/types.h"
#include "../inc/str_func.h"
#include <stdio.h>
#include <stdlib.h>

fofNode *Traverse (fofNode *root, char *path) {

  if (path == NULL) return root; // no where to traverse

  int len;
  char **split_path = str_split(path, ".", &len);

  for (int i = 0; i < len; i++) {
    root = get_sub_node(root, split_path[i]);
    if (root == NULL) return root;
  }

  for (int i = 0; i < len; i++) {
    free(split_path[i]);
  }
  free(split_path);

  return root;

}

STATUS_CODE SetInt (fofNode *root, char *path, int   val);
STATUS_CODE SetStr (fofNode *root, char *path, char *val);

NODE_TYPE GetType (fofNode *root, char *path);
int   GetInt      (fofNode *root, char *path);
char *GetStr      (fofNode *root, char *path);

StringInt   GetValue (fofNode *root, char *path);
STATUS_CODE SetValue (fofNode *root, char *path, StringInt val);

void Enumerate (fofNode *root, char *path, void (*callback)(char *path, StringInt val));

STATUS_CODE Delete (fofNode *root, char *path);
