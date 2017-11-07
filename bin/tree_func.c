#include "../inc/tree_func.h"
#include "../inc/fof_node.h"
#include "../inc/types.h"
#include "../inc/str_func.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

fofNode *Traverse (fofNode *root, char *path) {

  if (path == NULL) return root; // no where to traverse

  int len;
  char **split_path = str_split(path, ".", &len);

  for (int i = 0; i < len; i++) {
    root = get_sub_node(root, split_path[i]);
    if (root == NULL) break;
  }

  for (int i = 0; i < len; i++) {
    free(split_path[i]);
  }
  free(split_path);

  return root;

}

STATUS_CODE CreatePath (fofNode *root, char *path) {

  if (path == NULL) return PATH_NOT_DIRECTORY; // Nothing to create

  int len;
  char **split_path = str_split(path, ".", &len);
  StringInt empty_value;
  STATUS_CODE return_sc = OK;

  for (int i = 0; i < len; i++) {
    if (get_node_type(root) != FOLDER_NODE) {
      return_sc = PATH_NOT_DIRECTORY;
      break;
    }
    if (has_sub_node(root, split_path[i]) == false) {
      return_sc = add_sub_node(root, split_path[i], FOLDER_NODE, empty_value);
    }
    if (return_sc != OK) {break;}
    root = get_sub_node(root, split_path[i]);
  }

  for (int i = 0; i < len; i++) {
    free(split_path[i]);
  }
  free(split_path);

  return return_sc;

}

STATUS_CODE SetInt (fofNode *root, char *path, int val) {

  STATUS_CODE sc;

  // Get path to parrent node
  int parts_len;
  char **path_parts = str_split(path, ".", &parts_len);
  if (path_parts == NULL) return ALLOC_FAIL;
  char *parent_path = str_arr_join(path_parts, ".", parts_len-1);
  if (parent_path == NULL) {
    for (int i = 0; i< parts_len; i++) {
      free(path_parts[i]);
    }
    free(path_parts);
    return ALLOC_FAIL;
  }

  // save backup of pareeent_path
  char backup[strlen(parent_path)+1];
  strcpy(backup, parent_path);

  // Create path to parent if not exists
  sc = CreatePath(root, parent_path);
  if (sc == OK) {

    strcpy(parent_path, backup); // restore backup

    // Traverse to parent
    fofNode *parent = Traverse(root, parent_path);

    // Create subnode if not exists, if it does update value is correct type
    sc = add_sub_node(parent, path_parts[parts_len-1], INTEGER_NODE, (StringInt) val);
    if (sc == NODE_ALREADY_EXISTS) {
      // get the value node
      fofNode *node = get_sub_node(parent, path_parts[parts_len-1]);
      if (get_node_type(node) == INTEGER_NODE) {
        node->val_i = val;
        sc = OK;
      } else {
        sc = NODE_NOT_INTEGER;
      } // END type check
    } /* END allready exists*/

  } // END ok after CreatePath

  for (int i = 0; i< parts_len; i++) {
    free(path_parts[i]);
  }
  free(path_parts);
  free(parent_path);

  return sc;

}

STATUS_CODE SetStr (fofNode *root, char *path, char *val) {

  STATUS_CODE sc;

  // Get path to parrent node
  int parts_len;
  char **path_parts = str_split(path, ".", &parts_len);
  if (path_parts == NULL) return ALLOC_FAIL;
  char *parent_path = str_arr_join(path_parts, ".", parts_len-1);
  if (parent_path == NULL) {
    for (int i = 0; i< parts_len; i++) {
      free(path_parts[i]);
    }
    free(path_parts);
    return ALLOC_FAIL;
  }

  // save backup of parent_path
  char backup[strlen(parent_path)+1];
  strcpy(backup, parent_path);

  // Create path to parent if not exists
  sc = CreatePath(root, parent_path);
  if (sc == OK) {

    strcpy(parent_path, backup); // restore backup

    // Traverse to parent
    fofNode *parent = Traverse(root, parent_path);
    if (parent != NULL) { // Traverse failed

      // Create subnode if not exists, if it does update value if correct type
      sc = add_sub_node(parent, path_parts[parts_len-1], STRING_NODE, (StringInt) val);
      if (sc == NODE_ALREADY_EXISTS) {
        // get the value node
        fofNode *node = get_sub_node(parent, path_parts[parts_len-1]);
        if (get_node_type(node) == STRING_NODE) {

          // if new string is longer allock new mem
          if (strlen(node->val_c) < strlen(val)) {
            free(node->val_c);
            node->val_c = (char*) malloc(strlen(val)+1);
            strcpy(node->val_c, val);
          } else {
            strcpy(node->val_c, val);
          }
          sc = OK;

        } else {
          sc = NODE_NOT_INTEGER;
        } // END type check
      } /* END allready exists*/

    } // END parent != NULL

  } // END ok after CreatePath

  for (int i = 0; i< parts_len; i++) {
    free(path_parts[i]);
  }
  free(path_parts);
  free(parent_path);

  return sc;

}

NODE_TYPE GetType (fofNode *root, char *path, STATUS_CODE *sc) {

  fofNode *node = Traverse(root, path);
  if (node == NULL){
    if (sc != NULL) *sc = NODE_NOT_FOUND;
    return UNKNOWN;
  }

  return get_node_type(node);

}

int   GetInt (fofNode *root, char *path, STATUS_CODE *sc) {

  fofNode *node = Traverse(root, path);


}

char *GetStr      (fofNode *root, char *path);

StringInt   GetValue (fofNode *root, char *path);
STATUS_CODE SetValue (fofNode *root, char *path, StringInt val);

void Enumerate (fofNode *root, char *path, void (*callback)(char *, StringInt));

STATUS_CODE Delete (fofNode *root, char *path);
