#include "inc/types.h"
#include "inc/fof_node.h"
#include "inc/tree_func.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void print_sub_nodes(char *path, NODE_TYPE type, StringInt val) {

  if (type == INTEGER_NODE) {
    printf("%s = %d\n", path, val.i);
  } else {
    printf("%s = \"%s\"\n", path, val.c);
  }

}

int main(void) {

  /* ### Temp vars for inputs ### */
  char name[20] = "root";
  char path[80];
  StringInt val;
  STATUS_CODE sc;

  /* ### Setup ### */
  char file[17];
  strcpy(file, "./test_text.txt");
  fofNode *root = Initialize_from_file(file, &sc);
  if (sc != OK) {
    printf("Unexpected error in Initialize_from_file() : 28:19\n");
    return -1;
  }

  //fofNode *root = new_fofNode(name, FOLDER_NODE, val);

  // Lest first create some paths and values
  //strcpy(path, "strings.no.header");
  //strcpy(name, "\"Random title here\"");

  //sc = SetValue(root, path, name);
  //if (sc != OK) {
  //  printf("Unexpected error in SetStr() : 23:8\n");
  //  return -1;
  //}

  // Get a value to see if it works

  strcpy(path, "strings.no.header");
  val.c = GetStr(root, path, &sc);
  if (sc != OK) {
    printf("Failed to get 'strings.no.header'\n");
  } else {
    printf("strings.no.header = %s\n", val.c);
  }

  // strcpy(path, "strings.no.header");
  // sc = Delete(root, path);
  // if (sc != OK) {
  //   printf("NOT deleted\n");
  // } else {
  //   printf("Deleted\n");
  // }

  // Cleanup
  printf("Cleanup\n");
  destroy_fofNode(root);
  printf("Cleanup\n");

  return 0;
}
