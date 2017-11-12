#include "inc/btree.h"
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

int main(int argc, char *argv[]) {

  // Check input arguments
  if (argc != 2) {
    printf("Invalid argument count\n");
    printf("Usage:\n");
    printf("  %s <filename>\n", argv[0]);
    return -1;
  }

  /* Variables for temporarily holding:
   * path, name, value, type, and status-code
   * for each test.
   */
  char name[20];
  char path[80];
  StringInt val;
  NODE_TYPE type;
  STATUS_CODE sc;

  /* ### Setup ### */
  printf("Setting up B-tree from file: '%s'\n", argv[1]);
  fofNode *root = Initialize_from_file(argv[1], &sc);
  if (sc == FILE_NOT_FOUND) {
    printf("File not found: '%s'\n", argv[1]);
    return -1;
  } else if (sc == ALLOC_FAIL) {
    printf("Allocation failure\n");
    return -1;
  } else if (sc != OK) {
    printf("Unexpected error in Initialize_from_file()\n");
    return -1;
  }
  printf("B-tree setup done.\n");
  printf("\n----------------------------------\n\n");

  // ### GetStr() Test
  printf("GetStr() Test:\n");

  strcpy(path, "strings.no.text");
  val.c = GetStr(root, path, &sc);
  if (sc != OK) {
    printf("Failed to get 'strings.no.text'\n");
  } else {
    printf("strings.no.text = %s\n", val.c);
  }
  printf("\n----------------------------------\n\n");

  // ### GetInt() Test
  printf("GetInt() Test:\n");

  strcpy(path, "config.update.interval");
  val.i = GetInt(root, path, &sc);
  if (sc != OK) {
    printf("Failed to get 'config.update.interval'\n");
  } else {
    printf("config.update.interval = %d\n", val.i);
  }
  printf("\n----------------------------------\n\n");

  // ### Testing GetType() and GetValue()
  printf("Testing GetType() in conjunction with GetValue():\n");

  strcpy(path, "config.update.server1");
  type = GetType(root, path, &sc);
  if (sc != OK) {
    printf("Could not get type of 'config.update.server1'\n");
  } else {
    printf("Type of 'config.update.server1' was '%s'\n", type == STRING_NODE ? "String" : "Int");

    // So lets do the GetValue part
    strcpy(path, "config.update.server1");

    val = GetValue(root, path, &sc);
    if (sc != OK) {
      printf("Could not get value of 'config.update.server1'\n");
    } else {
      if (type == STRING_NODE) {
        printf("'config.update.server1' = %s\n", val.c);
      } else {
        printf("'config.update.server1' = %d\n", val.i);
      } // END if type chech
    } // END if status check
  } // END if status check of GetType()

  printf("\n");

  // Now on a integer node
  strcpy(path, "config.update.timeout");
  type = GetType(root, path, &sc);
  if (sc != OK) {
    printf("Could not get type of 'config.update.timeout'\n");
  } else {
    printf("Type of 'config.update.timeout' was '%s'\n", type == STRING_NODE ? "String" : "Int");

    // So lets do the GetValue part
    strcpy(path, "config.update.timeout");

    val = GetValue(root, path, &sc);
    if (sc != OK) {
      printf("Could not get value of 'config.update.timeout'\n");
    } else {
      if (type == STRING_NODE) {
        printf("'config.update.timeout' = %s\n", val.c);
      } else {
        printf("'config.update.timeout' = %d\n", val.i);
      } // END if type chech
    } // END if status check
  } // END if status check of GetType()
  printf("\n----------------------------------\n\n");

  // ### END GetType() and GetValue() Test

  // Enumerate() Test
  printf("Enumerate() Test:\n");

  strcpy(path, "strings.*.*");
  printf("Path to Enumerate = '%s'\n\n", path);
  Enumerate(root, path, &print_sub_nodes);
  printf("\n----------------------------------\n\n");

  // ### Delete() Test
  printf("Delete() Test:\n");

  strcpy(path, "strings.no.header");
  sc = Delete(root, path);
  if (sc != OK) {
    printf("Failed to delete\n");
  } else {
    printf("Deleted 'strings.no.header'\n");
  }
  printf("\n----------------------------------\n\n");

  // ### Cleanup
  printf("Cleanup...\n");
  destroy_fofNode(root);
  printf("Cleanup Done!\n");

  return 0;
}
