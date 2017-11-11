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
  strcpy(file, "../test_text.txt");
  fofNode *root = Initialize_from_file(file, &sc);
  if (sc != OK) {
    printf("Unexpected error in Initialize_from_file() : 28:19\n");
    return -1;
  }

  // Lest first create some paths and values
  // strcpy(path, "strings.no.header");
  // strcpy(name, "\"Random title here\"");
  //
  // sc = SetValue(root, path, name);
  // if (sc != OK) {
  //   printf("Unexpected error in SetStr() : 23:8\n");
  //   return -1;
  // }
  //
  // strcpy(path, "strings.no.size");
  // strcpy(name, "42");
  //
  // sc = SetValue(root, path, name);
  // if (sc != OK) {
  //   printf("Unexpected error in SetInt() : 31:8\n");
  //   return -1;
  // }

  // Lets see if we get the expected error if we try to add a value on a invalid path
  strcpy(path, "strings.no");

  sc = SetStr(root, path, name);
  if (sc != NODE_NOT_STRING) {
    printf("Unexpexted error in SetStr() | did not get NODE_NOT_STRING err\n");
    return -1;
  }

  // ## TEST enumeration

  strcpy(path, "strings.no.*");

  printf("Emunerate test on path = strings.no.*:\n\n");
  Enumerate(root, path, print_sub_nodes);
  printf("\n-----------------------------------\n\n");


  // Print all values before we try changling it
  strcpy(path, "strings.no.header");
  char *vs = GetStr(root, path, &sc);
  if (sc != OK) {
    printf("Unexpected error in GetStr() : 47:14\n");
    return -1;
  }

  strcpy(path, "config.update.interval");
  int vi = GetInt(root, path, &sc);
  if (sc != OK) {
    printf("Unexpected error in GetInt() : 54:13\n");
    return -1;
  }

  // type check
  strcpy(path, "config.update.interval");
  bool type_check = GetType(root, path, &sc) == INTEGER_NODE;
  if (sc != OK) {
    printf("Unexpected error in GetType() : 64:21\n");
    return -1;
  }

  printf("First print:\n\n");
  printf("String: %s\n", vs);
  printf("Integer: %d\n", vi);
  printf("Type check %s\n", type_check ? "passed":"failed");
  printf("\n-----------------------------------\n\n");

  // Lest change the values
  strcpy(path, "strings.no.header");
  strcpy(name, "Some new title");

  sc = SetStr(root, path, name);
  if (sc != OK) {
    printf("Unexpected error in SetStr() : 70:8\n");
    return -1;
  }

  strcpy(path, "config.update.interval");

  sc = SetInt(root, path, 64);
  if (sc != OK) {
    printf("Unexpected error in SetInt() : 78:8\n");
    return -1;
  }

  // Now print he new values
  strcpy(path, "strings.no.header");
  vs = GetStr(root, path, &sc);
  if (sc != OK) {
    printf("Unexpected error in GetStr() : 86:8\n");
    return -1;
  }

  strcpy(path, "config.update.interval");
  vi = GetInt(root, path, &sc);
  if (sc != OK) {
    printf("Unexpected error in GetInt() : 93:8\n");
    return -1;
  }

  printf("Print after change:\n\n");
  printf("String: %s\n", vs);
  printf("Integer: %d\n", vi);
  printf("\n-----------------------------------\n\n");

  // value in root
  strcpy(path, "value");
  strcpy(name, "some val");

  sc = SetStr(root, path, name);
  if (sc != OK) {
    printf("Unexpected error in SetStr() : 121:8\n");
    return -1;
  }

  // print it
  strcpy(path, "value");
  vs = GetStr(root, path, &sc);
  if (sc != OK) {
    printf("Unexpected error in GetStr() : 129:8\n");
    return -1;
  }

  printf("Value as root sub node:\n\n");
  printf("String: %s\n", vs);
  printf("\n-----------------------------------\n\n");

  // ### GetValue() and Delete() test
  // first get value to test positive resoult
  strcpy(path, "strings.no.header");
  val = GetValue(root, path, &sc);
  if (sc != OK) {
    printf("Unexpected error in GetValue() : 152:9\n");
    return -1;
  }

  printf("Resoult of GetValue() (string): %s\n", val.c);
  printf("\n-----------------------------------\n\n");

  printf("deleting 'strings.no.header'\n");
  // now lest delete the node
  strcpy(path, "strings.no.header");
  sc = Delete(root, path);
  if (sc != OK) {
    printf("Unexpected error in Delete() : 164:8\n");
    return -1;
  }
  printf("deleted\n");

  printf("getting 'strings.no.header\n");
  // get val ater delete
  strcpy(path, "strings.no.header");
  val = GetValue(root, path, &sc);
  if (sc == NODE_NOT_FOUND) {
    printf("Expected error in GetValue() : 172:9\n - NODE_NOT_FOUND\n");
  } else {
    printf("Resoult of GetValue() after Delete() (string): %s\n", val.c);
  }

  printf("\n-----------------------------------\n\n");

  // Cleanup
  printf("Cleanup\n");
  destroy_fofNode(root);
  printf("Cleanup\n");

  return 0;
}
