#include "../inc/tree_func.h"
#include "../inc/fof_node.h"
#include "../inc/str_func.h"
#include "../inc/types.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/stat.h>

fofNode *Initialize_from_file(char *filename, STATUS_CODE *sc) {

  struct stat sBuffer;
  int iRc;

  iRc = stat(filename, &sBuffer);
  if (iRc == -1) { *sc = FILE_NOT_FOUND; return NULL; }

  char name[5];
  strcpy(name, "root");
  StringInt empty_value;
  fofNode *root = new_fofNode(name, FOLDER_NODE, empty_value);
  if (root == NULL) { *sc = ALLOC_FAIL; return NULL; }

  //printf("malloc\n");
  char *path = (char*) malloc(256);
  if (path == NULL) {
    destroy_fofNode(root);
    *sc = ALLOC_FAIL;
    return NULL;
  }
  char *val = (char*) malloc(256);
  if (val == NULL) {
    destroy_fofNode(root);
    free(path);
    *sc = ALLOC_FAIL;
    return NULL;
  }

  FILE *fp = fopen(filename, "r");

  while (2 == fscanf(fp, "%s%*[ ]=%*[ ]%[^\n]", path, val)) {
    //printf("while\n");

    //printf("Path : %s\n", path);
    //printf("Val  : %s\n", val);

    SetValue(root, path, val);

  }

  fclose(fp);

  //printf("done\n");

  free(path);
  free(val);

  *sc = OK;

  return root;

}

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

STATUS_CODE SetInt (fofNode *root, char *path, int value) {

  STATUS_CODE sc;
  StringInt val;
  val.i = value;

  // Get path to parent node
  int parts_len;
  char **path_parts = str_split(path, ".", &parts_len);
  if (path_parts == NULL) return ALLOC_FAIL;
  char *parent_path = str_arr_join(path_parts, ".", 0, parts_len-1);
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
        node->val_i = val.i;
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

STATUS_CODE SetStr (fofNode *root, char *path, char *value) {

  STATUS_CODE sc;
  StringInt val;
  val.c = value;

  // Get path to parent node
  int parts_len;
  char **path_parts = str_split(path, ".", &parts_len);
  if (path_parts == NULL) { return ALLOC_FAIL; }

  char *parent_path = str_arr_join(path_parts, ".", 0, parts_len-1);
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
    if (parent != NULL) { // Traverse succsess

      // Create subnode if not exists, if it does update value if correct type

      sc = add_sub_node(parent, path_parts[parts_len-1], STRING_NODE, val);
      if (sc == NODE_ALREADY_EXISTS) {
        // get the value node
        fofNode *node = get_sub_node(parent, path_parts[parts_len-1]);
        if (get_node_type(node) == STRING_NODE) {

          // if new string is longer allock new mem
          if (strlen(node->val_c) < strlen(val.c)) {
            free(node->val_c);
            node->val_c = (char*) malloc(strlen(val.c)+1);
            strcpy(node->val_c, val.c);
          } else {
            strcpy(node->val_c, val.c);
          }
          sc = OK;

        } else {
          sc = NODE_NOT_STRING;
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

  if (sc != NULL) *sc = OK;

  return get_node_type(node);

}

char *GetText(fofNode *root, char *name, STATUS_CODE *sc) {

  if (strcmp(root->pszName, name) == 0) { // is this the correct node
    if (get_node_type(root) == STRING_NODE) { // is it type string
      *sc = OK;
      return root->val_c;
    } else {
      // wrong type
      *sc = NODE_NOT_STRING;
      return NULL;
    }
  }

  if (get_node_type(root) == FOLDER_NODE) {
    // resurese down all nodes til the node is found
    for (size_t i = 0; i < root->nodeCount; i++) {
      char *out = GetText(root->pChildren[i], name, sc);
      if (*sc == NODE_NOT_STRING || *sc == OK) {// Eighter of these means the node was found
        return out;
      }
    } // END for i
  } // END type == FOLDER_NODE

  // if this is not the correct node and is not a folder the node was not found
  *sc = NODE_NOT_FOUND;
  return NULL;

}

int GetInt (fofNode *root, char *path, STATUS_CODE *sc) {

  fofNode *node = Traverse(root, path);
  if (node == NULL){
    if (sc != NULL) *sc = NODE_NOT_FOUND;
    return 0;
  }

  if (get_node_type(node) != INTEGER_NODE) {
    if (sc != NULL) *sc = NODE_NOT_INTEGER;
    return 0;
  }

  if (sc != NULL) *sc = OK;

  return node->val_i;

}

char *GetStr (fofNode *root, char *path, STATUS_CODE *sc) {

  fofNode *node = Traverse(root, path);
  if (node == NULL){
    if (sc != NULL) *sc = NODE_NOT_FOUND;
    return NULL;
  }

  if (get_node_type(node) != STRING_NODE) {
    if (sc != NULL) *sc = NODE_NOT_STRING;
    return 0;
  }

  if (sc != NULL) *sc = OK;

  return node->val_c;

}

StringInt GetValue (fofNode *root, char *path, STATUS_CODE *sc) {

  StringInt empty_value;

  fofNode *node = Traverse(root, path);
  if (node == NULL){
    if (sc != NULL) *sc = NODE_NOT_FOUND;
    return empty_value;
  }

  NODE_TYPE type = get_node_type(node);

  if (type == FOLDER_NODE || type == UNKNOWN) {
    if (sc != NULL) *sc = NODE_NOT_VALUE;
    return empty_value;
  }

  StringInt out;

  if (type == STRING_NODE) {
    out.c = node->val_c;
  } else {
    out.i = node->val_i;
  }

  if (sc != NULL) *sc = OK;

  return out;

}

STATUS_CODE SetValue (fofNode *root, char *path, char *val) {

  STATUS_CODE sc;

  if (val[0] == '"') {

    char *clean_val = str_filter_out(val, "\"");
    sc = SetStr(root, path, clean_val);
    free(clean_val);

  } else {

    int i_val = atoi(val);
    sc = SetInt(root, path, i_val);

  }

  return sc;

}

STATUS_CODE Enumerate  (fofNode *root, char *path, EnumerationCallback *callback) {

  // split path
  int len;
  char **split_path = str_split(path, ".", &len);

  STATUS_CODE sc = _enumerate(root, split_path, len, 0, callback);

  for (int i = 0; i < len; i++) {
    free(split_path[i]);
  }
  free(split_path);

  return sc;

}

STATUS_CODE _enumerate (fofNode *root,
                        char **path,
                        int len,
                        int index,
                        EnumerationCallback *callback) {

  // First off we check if we've reached the en of the path
  if (index >= len) {
    // in this case just call the callback with the root node
    char *full_path = str_arr_join(path, ".", 0, len);

    STATUS_CODE sc;
    StringInt val = GetValue(root, NULL, &sc);
    if (sc != OK) {
      free(full_path);
      return sc;
    }

    callback(full_path, get_node_type(root), val);

    free(full_path);
    return OK;

  }

  // If the current index of path is '*' we need to recurse over all sub-nodes
  if (strcmp(path[index], "*") == 0) {
    // to enumerate we need to make sure the root is a FOLDER_NODE
    if (get_node_type(root) != FOLDER_NODE) { return PATH_NOT_DIRECTORY; }

    // now we go through all sub-nodes and replace the current path('*')
    // with the nodes name and recurse trough all
    // so we need to backup that char*
    char *backup = path[index];
    // we also need to keep track of the STATUS_CODE
    STATUS_CODE sc;
    for (int i = 0; i < root->nodeCount; i++) {

      char *node_name = root->pChildren[i]->pszName;
      path[index] = node_name;

      // we let the next round of the function handle the traversing
      sc = _enumerate(root, path, len, index, callback);

      if (sc != OK) { path[index] = backup; return sc; }

    } // END for i

    path[index] = backup;

    return OK;

  } // END If path[index] == "*"

  // if we get here we just need to traverse and recurse
  // make sure root has the subnode specified by path
  if (has_sub_node(root, path[index]) == false) { return INVALID_PATH; }

  return _enumerate(get_sub_node(root, path[index]), path, len, index+1, callback);

}

STATUS_CODE Delete (fofNode *root, char *path) {

  // we need to traverse to parent so lets parse the path to get the path to prent.
  int len;
  char **path_parts = str_split(path, ".", &len);
  if (path_parts == NULL) {return ALLOC_FAIL;} // if failed to split return.
  // Now we have the path as seperate parts.
  // Now join all but the node that we want to delete
  char *parent_path = str_arr_join(path_parts, ".", 0, len-1);
  if (parent_path == NULL) { // if failed to join
    // Cleanup
    for (int i = 0; i< len; i++) {
      free(path_parts[i]);
    }
    free(path_parts);
    return ALLOC_FAIL;
  }

  STATUS_CODE sc = OK;

  // Ok now we can traverse to parent and try deleting the child
  fofNode *parent = Traverse(root, parent_path);
  if (parent == NULL) { sc = NODE_NOT_FOUND; }
  if (sc == OK) {

    // del_sub_node() handles the rest
    sc = del_sub_node(parent, path_parts[len-1]);

  }

  // remember to clean up
  for (int i = 0; i< len; i++) {
    free(path_parts[i]);
  }
  free(path_parts);
  free(parent_path);

  return sc;

}
