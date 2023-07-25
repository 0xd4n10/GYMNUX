#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include "../include/routine.h"

#include "../include/main.h"

#include <sys/types.h>

#include <sys/stat.h>


void clearScreen() {
  system("clear"); 
}

int init(struct routine_collection * newCollection) {
  
  
  struct stat st;
  
  // if config file exists, parse into memory
  if (stat(CONFIG_F, & st) == 0) {
    parseRoutineCollectionFromJson(newCollection);
  }

  clearScreen();
  return 0;
}

int main() {

  // Create routine collection
  struct routine_collection * MyRoutineCol = NULL;
  MyRoutineCol = (struct routine_collection * ) calloc(10, sizeof(struct routine_collection));
  
  if (MyRoutineCol == NULL) {
    printf("Failed to allocate memory for routine collection!\n");
    return;
  }

  if (init(MyRoutineCol) != 0) {
    printf("Failed to parse routines into memory.\n");
    return;
  }
  // Print banner
  printf(BANNER);
  // Main command loop
  char command[MAX_COMMAND];
  while (1) {
    printf("\nGYMNUX > ");
    fgets(command, sizeof(command), stdin); // Get command from stdin
    command[strcspn(command, "\n")] = '\0'; // Remove trailing newline character
    executeCommand(command, MyRoutineCol);
  }
  return 0;
}