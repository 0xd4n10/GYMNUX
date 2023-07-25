#include "../include/main.h"

#include "../include/routine.h"

int validateCommand(const char * str, int argCount, char * help) {
  char * token;
  int count = 0;

  if (strlen(str) == 0) {
    printf(help);
    return -1;
  }

  if (strlen(str) >= MAX_NAME_LEN) {
    printf("Name too long!\n");
    return -1;
  }

  char strCopy[strlen(str) + 1];
  strcpy(strCopy, str);

  // Tokenize the string using space as the delimiter
  token = strtok(strCopy, " ");
  while (token != NULL) {
    count++;
    token = strtok(NULL, " ");
  }

  if (count != argCount) {
    printf(help);
    return -1;
  }
  return 0;
}

void routineShell(struct routine * croutine,
  const char * rName) {
  char rCommand[100];
  while (1) {
    printf("\n(%s) GYMNUX > ", rName);
    fgets(rCommand, sizeof(rCommand), stdin);
    rCommand[strcspn(rCommand, "\n")] = '\0'; // Remove trailing newline character
    executeRCommand(rCommand, croutine, rName);
  }
}

void executeRCommand(const char * rCommand,
  const struct routine * croutine,
    const char * rName) {
  if (strncmp(rCommand, "exit", 4) == 0) { // Exit higher level shell
    clearScreen();
    main();
  } else if (strncmp(rCommand, "help", 4) == 0) { // Show help
    printf(HELPR);
    return;
  } else if (strncmp(rCommand, "add ", 4) == 0) { // Add set

    char * args = rCommand + 4;

    if (validateCommand(args, 2, HELPR) != 0) {
      return;
    }

    char * arglist[1];
    int wordCount = 0;
    char * token = strtok(args, " ");
    while (token != NULL && wordCount < 3) {
      if (wordCount == 2) {
        printf(BADHELPR);
        break;
      }
      arglist[wordCount] = malloc(50 * sizeof(char));

      strncpy(arglist[wordCount], token, 50 - 1);
      arglist[wordCount][50 - 1] = '\0';

      token = strtok(NULL, " ");

      wordCount++;
    }
    if (arglist[1] == NULL || arglist[0] == NULL) {
      printf(BADHELPR);
      return;
    }

    char * setName = arglist[0];

    int addTime = atoi(arglist[1]);
    if (addTime < 0 || addTime >= MAX_TIME) {
      printf("That's too long!");
      return;
    }
    if (!addTime) {
      printf("Bad usage!\n");
      printf(HELPR);
      return;
    }

    addSet(croutine, setName, addTime, rName);

    writeRoutineCollectionToJson(croutine); // Update config file
  } else if (strncmp(rCommand, "rest ", 5) == 0) { // Update rest time for routine
    char * args = rCommand + 5;

    if (validateCommand(args, 1, HELP) != 0) {
      return;
    }
    int restTime = atoi(args);
    if (restTime < 0 || restTime >= MAX_TIME) {
      printf("That's too long!");
      return;
    }
    if (!restTime) {
      printf("Bad usage!\n");
      printf(HELPR);
      return;
    }
    // DO REST COMMAND
    addRest(croutine, restTime, rName);
    writeRoutineCollectionToJson(croutine);

  } else if (strncmp(rCommand, "start", 5) == 0) { // Start
    start(croutine, rName);

  } else if (strncmp(rCommand, "list", 5) == 0) { // List sets and rest information
    listSets(croutine, rName);

  } else {
    printf("Bad command!\n\n");
    printf(HELPR);
  }

}
void executeCommand(const char * command, struct routine_collection * collection) {
    if (strcmp(command, "exit") == 0) {
      exit(0);
    } else if (strcmp(command, "help") == 0) { // Show help for main shell
      printf(HELP);
    } else if (strncmp(command, "add ", 4) == 0) { // add routine
      if (strlen(command) < 5) {
        printf(HELP);
        return;
      }
      char * rname = command + 4;
      if (validateCommand(rname, 1, HELP) != 0) {
        return;
      }
      
      struct routine * myRoutine = (struct routine * ) calloc(10, sizeof(struct routine));
      if (myRoutine == NULL) {
        printf("Failed to allocate memory for new routine.\n");
        return;
      }
      strncpy(myRoutine -> name, rname, sizeof(myRoutine -> name) - 1);
      myRoutine -> name[sizeof(myRoutine -> name) - 1] = '\0';
      addRoutine(collection, myRoutine);
      writeRoutineCollectionToJson(collection);

    } else if (strncmp(command, "use ", 4) == 0) { // Use a routine
      const char * uroutine = command + 4;
      if (validateCommand(uroutine, 1, HELP) != 0){
        return;
      }
      
      if (checkRoutine(collection, uroutine) != 0) {
        printf("Routine doesn't exist! Use the list command to list routines.\n");
        return;
      }
      printf("Using routine %s\n", uroutine);
      routineShell(collection, uroutine);
    } else if (strncmp(command, "list", 4) == 0) {
      if (collection -> numRoutines == 0) {
        printf("No routines added yet!\nuse the add command to add a routine.\n");
        return;
      }
      printf("Routines: \n");
      listRoutines(collection);
    } else if (strncmp(command, "delete ", 7) == 0) { // Delete a routine.
      const char * uroutine = command + 7;
      if (validateCommand(uroutine, 1, HELP) != 0) {
        return;
      }

      if (checkRoutine(collection, uroutine) != 0) {
        printf("Routine doesn't exist! Use the list command to list routines.\n");
        return;
      }
      deleteRoutine(collection, uroutine);
      printf("Routine deleted!\n");
      writeRoutineCollectionToJson(collection);
    } else {
      printf("Bad command: %s\n\n", command);
      printf(HELP);
    }
}