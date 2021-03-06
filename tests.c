#include "inc/btree.h"
#include "inc/tests.h"
#include <stdio.h>
#include <string.h>

void print_sub_nodes(char *path, NODE_TYPE type, StringInt val) {

  if (type == INTEGER_NODE) {
    printf("%s = %d\n", path, val.i);
  } else {
    printf("%s = \"%s\"\n", path, val.c);
  }

}

void tests(fofNode *root) {

  /* Variables for temporarily holding:
   * path, name, value, type, and status-code
   * for each test.
   */
  char path[80];
  char name[20];
  StringInt val;
  NODE_TYPE type;
  STATUS_CODE sc;

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

  // ### Enumerate() Test
  printf("Enumerate() Test:\n");

  strcpy(path, "strings.*.*");
  printf("Path to Enumerate = '%s'\n\n", path);
  Enumerate(root, path, &print_sub_nodes);
  printf("\n----------------------------------\n\n");

  // ### GetText() Test
  printf("GetText() Test:\n");

  strcpy(name, "server1");
  val.c = GetText(root, name, &sc);
  if (sc != OK) {
    printf("Failed to find node by with name 'server1'\n");
  } else {
    printf("Node with name 'server1' = %s\n", val.c);
  }
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

}
