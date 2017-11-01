#include "../inc/types.h"
#include "../inc/fof_node.h"
#include <stdlib.h>
#include <string.h>

fofNode *new_fofNode(const char *name, NODE_TYPE type, StringInt val) {

  fofNode *node = (fofNode*) calloc(1, sizeof(fofNode));

  // set name
  node->pszName = (char*) malloc(strlen(name) + 1);
  strcpy(node->pszName, name);
  node->pszName[strlen(name)] = '\0';

  node->nodeCount = -1;

  // set value if string/integer node or nodeCount if folder
  if (type = FOLDER_NODE) {
    node->nodeCount = 0;
  } else if (type = STRING_NODE) {
    node->val_c = (char*) malloc(strlen(val->c) +1);
    strcpy(node->val_c, val->c);
    node->val_c[strlen(val->c)] = '\0';
    nodeCount = -1;
  } else {
    node->val_i = val->i;
    node->nodeCount = -1;
  }

  return node;

}

void destroy_fofNode(fofNode *pn) {

  NODE_TYPE type = get_node_type(pn);
  if (type = FOLDER_NODE) {

    // Node is folder
    // recurse through all child nodes
    while (pn->nodeCount > 0) {
      destroy_fofNode(pn->pChildren[pn->nodeCount-1]);
    }
    // then free the array itself
    free(pn->pChildren);

  } else if (type == STRING_NODE) {
    // Node is string
    // we only need to free the string
    free(pn->val_c);
  }

  // last free the actual node
  free(pn);

}

NODE_TYPE get_node_type(fofNode *pn) {

  if (pn->nodeCount > -1) return FOLDER_NODE;
  if (pn->val_c != NULL) return STRING_NODE;
  return INTEGER_NODE;

}

STATUS_CODE add_sub_node(fofNode *parent,
                         const char *name,
                         NODE_TYPE type,
                         StringInt val) {

  // code

}

STATUS_CODE del_sub_node(fofNode *parent, const char *name) {

  int del = 0; // bool if node was deleted
  for (int i = 0; i < parent->nodeCount; i++) {
    // If the node is already deleted move this node back in the array
    if (del) {
      parent->pChildren[i-1] = parent->pChildren[i];
    }
    // otherwise we find the node
    else if (strcmp(parent->pChildren[i]->pszName, name) == 0) {
      // we found is now destroy if
      destroy_fofNode(parent->pChildren[i]);
      del = 1;
    }
  }

  if (del) {
    // if node was found and deleted decrement nodeCount and realloc array
    parent->nodeCount--;
    parent->pChildren = (fofNode**) realloc(parent->pChildren, sizeof(fofNode*) * parent->nodeCount);
  }

}
