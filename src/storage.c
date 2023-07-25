#include "../include/main.h"

#include "../include/routine.h"

void writeRoutineCollectionToJson(const struct routine_collection * collection) {
  // Set config filename
  const char * filename = CONFIG_F;
  // Create json object
  struct json_object * rootObj = json_object_new_object();
  // Create json routine collection array
  struct json_object * routinesArray = json_object_new_array();
  // Add routines array
  json_object_object_add(rootObj, "routines", routinesArray);
  // Loop through and add routines
  for (int i = 0; i < collection -> numRoutines; i++) {
    // Current routine counter
    struct routine currentRoutine = collection -> routines[i];
    // Create new routine object
    struct json_object * routineObj = json_object_new_object();
    json_object_array_add(routinesArray, routineObj);
    // update information in json object
    json_object_object_add(routineObj, "name", json_object_new_string(currentRoutine.name));
    json_object_object_add(routineObj, "numSets", json_object_new_int(currentRoutine.numSets));
    json_object_object_add(routineObj, "restTime", json_object_new_int(currentRoutine.restTime));
    // Create set array and update
    struct json_object * workoutListArray = json_object_new_array();
    json_object_object_add(routineObj, "workoutList", workoutListArray);
    // Add sets to routine and update
    for (int j = 0; j < MAX_WORKOUTS; j++) {
      struct set currentSet = currentRoutine.workoutList[j];

      struct json_object * setObj = json_object_new_object();
      json_object_array_add(workoutListArray, setObj);

      json_object_object_add(setObj, "name", json_object_new_string(currentSet.name));
      json_object_object_add(setObj, "time", json_object_new_int(currentSet.time));
    }
  }
  // Write json object to config file
  const char * jsonString = json_object_to_json_string_ext(rootObj, JSON_C_TO_STRING_PRETTY);
  FILE * file = fopen(filename, "w");
  if (file != NULL) {
    fputs(jsonString, file);
    fclose(file);

  } else {

  }

  json_object_put(rootObj);
}


struct routine_collection * parseRoutineCollectionFromJson(struct routine_collection * collection) {
  
  collection -> numRoutines = 0;
  const char * filename = CONFIG_F;
  // open config file for parsing
  FILE * file = fopen(filename, "r");
  if (file != NULL) {
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    // allocate memory for parsed json data
    char * jsonData = (char * ) calloc(1, fileSize + 1);

    fread(jsonData, 1, fileSize, file);

    jsonData[fileSize] = '\0';

    fclose(file);
    // Create json object for parsed routine collection
    struct json_object * rootObj = json_tokener_parse(jsonData);
    free(jsonData);

    const char * json_str = json_object_to_json_string(rootObj);

    struct json_object * routinesArray;
    if (json_object_object_get_ex(rootObj, "routines", & routinesArray)) {
      int numRoutines = json_object_array_length(routinesArray);

      collection -> numRoutines = numRoutines;
      // Loop through routines
      for (int i = 0; i < numRoutines; i++) {
        struct json_object * routineObj = json_object_array_get_idx(routinesArray, i);

        //set name
        struct json_object * name;
        if (json_object_object_get_ex(routineObj, "name", & name)) {

          strncpy(collection -> routines[i].name, json_object_get_string(name), sizeof(collection -> routines[i].name) - 1);
          collection -> routines[i].name[sizeof(collection -> routines[i].name) - 1] = '\0';

        }
        // Update number of sets
        struct json_object * numSets;
        if (json_object_object_get_ex(routineObj, "numSets", & numSets)) {
          collection -> routines[i].numSets = json_object_get_int(numSets);
        }
        // Update rest time
        struct json_object * restTime;
        if (json_object_object_get_ex(routineObj, "restTime", & restTime)) {
          collection -> routines[i].restTime = json_object_get_int(restTime);
        }
        // Update workout list array
        struct json_object * workoutListArray;
        if (json_object_object_get_ex(routineObj, "workoutList", & workoutListArray)) {
          int numSets = json_object_array_length(workoutListArray);

          for (int j = 0; j < numSets; j++) {
            struct json_object * setObj = json_object_array_get_idx(workoutListArray, j);

            struct json_object * setName;
            if (json_object_object_get_ex(setObj, "name", & setName)) {

              strncpy(collection -> routines[i].workoutList[j].name, json_object_get_string(setName), sizeof(collection -> routines[i].workoutList[j].name) - 1);
              collection -> routines[i].workoutList[j].name[sizeof(collection -> routines[i].workoutList[j].name) - 1] = '\0';

            }

            struct json_object * time;
            if (json_object_object_get_ex(setObj, "time", & time)) {
              collection -> routines[i].workoutList[j].time = json_object_get_int(time);

            }
          }
        }
      }
    }

    json_object_put(rootObj);
  } else {
    printf("Failed to read config file!");
  }

  return collection;
}