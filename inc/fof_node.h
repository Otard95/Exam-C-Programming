#ifndef __FOF_NODE_H__
#define __FOF_NODE_H__

#include "types.h"
#include <stdbool.h>

typedef struct _FOF_NODE {

  char *pszName;
  int val_i;
  char *val_c;
  int nodeCount;
  _FOF_NODE **pChildren;

} fofNode;

fofNode *new_fofNode(char *name, NODE_TYPE type, StringInt val);
void destroy_fofNode(fofNode *pn);

NODE_TYPE get_node_type(fofNode *pn);
bool has_sub_node(fofNode *pn, char *name);

STATUS_CODE add_sub_node(fofNode *parent, char *name, NODE_TYPE type, StringInt val);
STATUS_CODE del_sub_node(fofNode *parent, char *name);

#endif // __FOF_NODE_H__
