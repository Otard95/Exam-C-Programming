#include "inc/btree.h"
#include "inc/tests.h"
#include <stdio.h>

int main(int argc, char *argv[]) {

  // Check input arguments
  if (argc != 2) {
    printf("Invalid argument count\n");
    printf("Usage:\n");
    printf("  %s <filename>\n", argv[0]);
    return -1;
  }

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

  // Run Test's
  tests(root);

  // ### Cleanup
  printf("Cleanup...\n");
  destroy_fofNode(root);
  printf("Cleanup Done!\n");

  return 0;
}
