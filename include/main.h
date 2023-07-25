#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <json-c/json.h>

#define BANNER "\n\n .88888.  dP    dP 8888ba.88ba  888888ba  dP     dP dP    dP \nd8'   `88 Y8.  .8P 88  `8b  `8b 88    `8b 88     88 Y8.  .8P \n88         Y8aa8P  88   88   88 88     88 88     88  Y8aa8P  \n88   YP88    88    88   88   88 88     88 88     88 d8'  `8b \nY8.   .88    88    88   88   88 88     88 Y8.   .8P 88    88 \n `88888'     dP    dP   dP   dP dP     dP `Y88888P' dP    dP \n\n\nby 0xd4n\n"
#define MAX_COMMAND 100 
#define MAX_NAME_LEN 50                         
#define MAX_TIME 65535                                   
#define CONFIG_F "../config/routines.json"
#define HELP  "GYMNUX Commands:\nadd ROUTINE-NAME: Add a routine\nlist: List routines\ndelete ROUTINE-NAME: delete a routine\nuse ROUTINE-NAME: use a routine\n"
#define BADHELP  "Bad command!\nadd ROUTINE-NAME: Add a routine\nlist: List routines\ndelete ROUTINE-NAME: delete a routine\nuse ROUTINE-NAME: use a routine\n"
#define HELPR "Routine commands:\nstart: start session!\nadd SET-NAME TIME: add a set\nlist: List sets\nrest REST-TIME: update rest time between sets\nexit: exit routine\n"
#define BADHELPR "Bad command!\nstart: start session!\nadd SET-NAME TIME: add a set\nlist: List sets\nrest REST-TIME: update rest time between sets\nexit: exit routine\n"
