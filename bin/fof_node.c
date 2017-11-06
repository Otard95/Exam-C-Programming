#include "../inc/types.h"
#include "../inc/fof_node.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

fofNode *new_fofNode(char *name, NODE_TYPE type, StringInt val) {

  fofNode *node = (fofNode*) calloc(1, sizeof(fofNode));

  // set name
  node->pszName = (char*) malloc(strlen(name) + 1);
  strcpy(node->pszName, name);

  node->nodeCount = -1;

  // set value if string/integer node or nodeCount if folder
  if (type == FOLDER_NODE) {
    node->nodeCount = 0;
  } else if (type == STRING_NODE) {
    node->val_c = (char*) malloc(strlen(val.c) +1);
    strcpy(node->val_c, val.c);
    node->nodeCount = -1;
  } else {
    node->val_i = val.i;
    node->nodeCount = -1;
  }

  return node;

}

void destroy_fofNode(fofNode *pn) {

  NODE_TYPE type = get_node_type(pn);
  if (type == FOLDER_NODE) {

    // Node is folder
    // recurse through all child nodes
    while (pn->nodeCount > 0) {
      destroy_fofNode((pn->pChildren[pn->nodeCount-1]));
      pn->nodeCount--;
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

bool has_sub_node(fofNode *pn, char *name) {

  if (get_node_type(pn) != FOLDER_NODE) return false;

  for (int i = 0; i < pn->nodeCount; i++) {
    // Find the node
    if (strcmp(pn->pChildren[i]->pszName, name) == 0) {
      // we found the node so lets return
      return true;
    }
  }

  // if we get here the node was not found
  return false;

}

STATUS_CODE add_sub_node(fofNode *parent,
                         char *name,
                         NODE_TYPE type,
                         StringInt val) {

  if (has_sub_node(parent, name)) return NODE_ALREADY_EXISTS;
  if (get_node_type(parent) != FOLDER_NODE) return NODE_NOT_FOLDER;

  // expand array
  fofNode **tmp_arr = (fofNode**) realloc(parent->pChildren, sizeof(fofNode*) * parent->nodeCount);
  if (tmp_arr == NULL) return ALLOC_FAIL; // return if fail
  parent->pChildren = tmp_arr;

  // create the new node
  fofNode *tmp_node = new_fofNode(name, type, val);
  if (tmp_node == NULL) return ALLOC_FAIL; // return if fail
  parent->pChildren[parent->nodeCount] = tmp_node;
  parent->nodeCount++;

  return OK;

}

STATUS_CODE del_sub_node(fofNode *parent, char *name) {

  int del = 0; // bool if node was deleted
  int nCount = parent->nodeCount;
  for (int i = 0; i < nCount; i++) {
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
    // if node was found and deleted, realloc array
    parent->pChildren = (fofNode**) realloc(parent->pChildren, sizeof(fofNode*) * parent->nodeCount);

    return OK;
  } else {
    return NODE_NOT_FOUND;
  }

}

fofNode *get_sub_node(fofNode *parent, char *name) {

  if (get_node_type(parent) != FOLDER_NODE) return NULL;

  for (int i = 0; i < parent->nodeCount; i++) {
    if (strcmp(parent->pChildren[i]->pszName, name) == 0) {
      return (parent->pChildren[i]);
    }
  }

  return NULL;

}
