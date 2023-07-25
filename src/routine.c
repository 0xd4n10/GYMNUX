#include "../include/routine.h"

#include <time.h>

void addRoutine(struct routine_collection * collection, struct routine * newRoutine) {
  if (collection) {
    // Check if routine already exists
    if (checkRoutine(collection, newRoutine -> name) == 0) {
      printf("Routine already exists!\n");
      return;
    }
    // Check if max routines has been reached
    if (collection -> numRoutines < MAX_ROUTINES) {
      // Initialize routine attributes to zero
      newRoutine -> numSets = 0;
      newRoutine -> restTime = 0;
      // Add routine to collection
      collection -> routines[collection -> numRoutines] = * newRoutine;
      // Update number of routines in collection
      collection -> numRoutines++;
      printf("Routine added successfully.\n");
    } else {
      printf("Cannot add routine. Maximum number of routines reached.\n");
    }
  }
}

void deleteRoutine(struct routine_collection * collection,
  const char * rName) {
  if (collection) {
    // Loop through routines
    for (int i = 0; i <= collection -> numRoutines - 1; i++) {
      // Find and delete routine
      if (strcmp(rName, collection -> routines[i].name) == 0) {
        // Shift remaining routines to the left
        collection -> routines[i] = collection -> routines[i+1];
        collection -> numRoutines -= 1;
        i++;
        for (int j = i; j <= collection -> numRoutines - 1; j++){
          collection -> routines[j] = collection -> routines[j+1];
        }
        return;
      }

    }
    printf("Routine not found!\n");
  }

}

void listSets(struct routine_collection * collection,
  const char * rName) {
  if (collection) {
    // Loop through routines
    for (int i = 0; i <= collection -> numRoutines - 1; i++) {
      if (strcmp(rName, collection -> routines[i].name) == 0) {
        // Check if sets exist
        if (collection -> routines[i].numSets == 0) {
          printf("No sets added yet\n");
          return;
        }
        printf("Rest time: %d seconds\nSets:\n", collection -> routines[i].restTime);
        // Loop through and print sets
        for (int j = 0; j < collection -> routines[i].numSets; j++) {
          if (strcmp(collection -> routines[i].workoutList[j].name, "") == 0) {
            return;
          }
          printf("%s : %d seconds\n", collection -> routines[i].workoutList[j].name, collection -> routines[i].workoutList[j].time);
        }
        return;
      }
    }
  }
}

void addSet(struct routine_collection * collection,
  const char * name,
    const int * time,
      const char * rName) {
  if (collection) {
    // Loop through routines
    for (int i = 0; i <= collection -> numRoutines - 1; i++) {
      // If selected routine
      if (strcmp(rName, collection -> routines[i].name) == 0) {
        // Check if max sets reached
        if (collection -> routines[i].numSets >= MAX_WORKOUTS) {
          printf("Max sets reached!\n");
          return;
        }
        
        // Add set and update sets counter
        int setNum = collection -> routines[i].numSets;
        collection -> routines[i].numSets++;
        strcpy(collection -> routines[i].workoutList[setNum].name, name);
        collection -> routines[i].workoutList[setNum].time = time;
        printf("set added\n");
      }
    }
  }
}

void addRest(struct routine_collection * collection,
  const int * time,
    const char * rName) {
  if (collection) {
    // Loop through and find selected routine
    for (int i = 0; i <= collection -> numRoutines; i++) {
      if (strcmp(rName, collection -> routines[i].name) == 0) {
        // Update rest time
        collection -> routines[i].restTime = time;
        printf("rest time updated\n");
      }
    }
  }
}
void start(struct routine_collection * collection,
  const char * rName) {
  if (collection) {
    // Find selected routine
    for (int i = 0; i <= collection -> numRoutines; i++) {
      if (strcmp(rName, collection -> routines[i].name) == 0) {
        // Check if sets exist
        if (collection -> routines[i].numSets == 0) {
          printf("No sets added yet!\n");
          return;
        }
        //beep 3 times
        for (int i = 0; i < 2; i++) {

          beep("high");
          usleep(500000);
        }
        // Loop through sets and sound buzzer
        for (int j = 0; j < collection -> routines[i].numSets; j++) {
          // Check if reached end of sets
          if (strcmp(collection -> routines[i].workoutList[j].name, "") == 0) {
            return;
          }
          printf("set %d: %s\n", j, collection -> routines[i].workoutList[j].name);
          beep("high");
          sleep(collection -> routines[i].workoutList[j].time);
          if (collection -> routines[i].restTime != 0) {
            printf("REST\n");
            beep("low");
            sleep(collection -> routines[i].restTime);
          }

        }
        beep("low");
        usleep(500000);
        beep("low");

      }

    }
  }
}
void listRoutines(struct routine_collection * collection) {
  // List routines
  for (int i = 0; i <= collection -> numRoutines - 1; i++) {
    printf("%d: %s\n", i + 1, collection -> routines[i].name);
  }
}

int checkRoutine(struct routine_collection * collection,
  const char * rName) {
  for (int i = 0; i < collection -> numRoutines; i++) {
    // If routine exists return zero, otherwise return -1
    if (strcmp(collection -> routines[i].name, rName) == 0) {
      return 0;
    }
  }
  return -1;
}