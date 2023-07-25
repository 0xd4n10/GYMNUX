#ifndef ROUTINE_H
#define ROUTINE_H

#define MAX_WORKOUTS 20
#define MAX_ROUTINES 20

// Struct definition for 'Set'
struct set {
    char name[50];
    unsigned short int time;
};

// Struct definition for 'Routine'
struct routine {
    char name[50];
    unsigned short int numSets;
    unsigned short int restTime;
    struct set workoutList[20];
};

// Structure definition for 'Routine Collection'
struct routine_collection {
    unsigned short int numRoutines;
    struct routine routines[MAX_ROUTINES];
};
#endif /* ROUTINE_H */

