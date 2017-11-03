#include "inc/types.h"
#include "inc/fof_node.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {

  // Create root
  char new_name[80];
  strcpy(new_name, "root");
  StringInt new_val;

  fofNode *root = new_fofNode(new_name, FOLDER_NODE, new_val);

  // Add first str node as subnode
  strcpy(new_name, "char1");
  new_val.c = "Hello_world";

  STATUS_CODE ret = add_sub_node(root, new_name, STRING_NODE, new_val);

  if (ret != OK) { // if it failed
    printf("Unexpected error\n");
    free(root); // clear mem
    return -1;
  }

  // Try to add same str mode again
  ret = add_sub_node(root, new_name, STRING_NODE, new_val);

  if (ret == NODE_ALREADY_EXISTS) { // we're expecting it to exist
    printf("Test passed | not adding duplicate\n");
  } else {
    printf("Test failed | adding duplicates\n");
    // clear mem
    destroy_fofNode(root);
    return -2;
  }

  // lets add our first integer node
  strcpy(new_name, "int_eger1");
  new_val.i = 42;

  ret = add_sub_node(root, new_name, INTEGER_NODE, new_val);

  if (ret != OK) {
    printf("Unexpected error\n");
    destroy_fofNode(root);
    return -3;
  }

  // and now lest try adding a child to the int node
  strcpy(new_name, "inpossible_subnode");

  ret = add_sub_node((root->pChildren[1]), new_name, INTEGER_NODE, new_val);

  if (ret == NODE_NOT_FOLDER) {
    printf("Test passed | can't add child to value node\n");
  } else {
    printf("Test failed | added child to value node\n");
    destroy_fofNode(root);
    return -4;
  }

  printf("root->pszName = %s\n", root->pszName);
  printf("root->pChildren[0]->pszName = %s\n", (root->pChildren[0])->pszName);
  printf("root->pChildren[0]->val_c = %s\n", (root->pChildren[0])->val_c);
  printf("root->pChildren[1]->pszName = %s\n", (root->pChildren[1])->pszName);
  printf("root->pChildren[1]->val_i = %d\n", (root->pChildren[1])->val_i);

  // clean up before exit
  destroy_fofNode(root);

  return 0;
}
