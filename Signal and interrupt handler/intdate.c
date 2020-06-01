//////////////////////////////////////////////////////////////////////////////////
//
// Copyright 2019 Jim Skrentny
// Posting or sharing this file is prohibited, including any changes/additions.
//
///////////////////////////////////////////////////////////////////////////////
// Main File:        intdate.c
// This File:        intdate.c
// Other Files:      
// Semester:         CS 354 Fall 2019
//
// Author:           Pulkit Goyal
// Email:            pgoyal22@wisc.edu
// CS Login:         pulkit
//
/////////////////////////// OTHER SOURCES OF HELP /////////////////////////////
//                   fully acknowledge and credit all sources of help,
//                   other than Instructors and TAs.
//
// Persons:          Identify persons by name, relationship to you, and email.
//                   Describe in detail the the ideas and help they provided.
//
// Online sources:   avoid web searches to solve your problems, but if you do
//                   search, be sure to include Web URLs and description of
//                   of any information you find.
///////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
/* counts number of SIGUSR1 signals that are caught */
int numSigusr1 = 0;

/* This function handles alarms 
 *
 * sig  signal number 
 * 
 */
void handler(int sig){
   /* saves date and time */
   time_t currentTime;
   /* checks if ctime works properly */
   char * check;
   /* checks if time function works properly and exit if there is an error */
   if(time(&currentTime) == -1){
     perror("Error");
     exit(1);
   }

   printf("PID: %d",getpid());           
   /* checks if ctime function works properly and exit if there is an error */
   if((check = ctime(&currentTime)) == NULL){
     perror("Error");
     exit(1);  
   }
   
   printf(" | Current Time: %s", check);
   /* checks if alarm function works properly and exit if there is an error */
   if(alarm(3) != 0){
     perror("Error");
     exit(1);
   }
}
/* This function handles SIGINT signals 
 *
 * sig  signal number 
 * 
 */
void sigIntHdl (int sig){
   /* print number of SIGUSR1 signals recieved and exit gracefully */
   printf("\nSIGINT received.\n");	   
   printf("SIGUSR1 was received %d", numSigusr1);
   printf(" times. Exiting now.\n");
   exit(0);
}

/* This function handles SIGUSR1 signals 
 *
 * sig  signal number 
 * 
 */
void sigusr1Hdl(int sig){
   /* print number of SIGUSR1 signals recieved and exit gracefully */
   numSigusr1++;
   printf("SIGUSR1 caught\n");
}

/* This function calls signal handler to handle appropriate signal  
 * 
 * returns 1 if an error occurs or 0 if everything works 
 */
int main(){
  /* print starting message */
  printf("Pid and time will be printed every 3 seconds.\n");
  printf("Enter ^C to end the program.\n");
  
  /* create three sigaction structs to handle the right signals */
  struct sigaction act;
  struct sigaction sigint_act;
  struct sigaction sigusr1_act;
  /* reset all three sigaction structs */
  memset(&act, 0, sizeof(act));
  memset(&sigint_act, 0, sizeof(sigint_act));
  memset(&sigusr1_act, 0, sizeof(sigusr1_act));
  /* call alarm */
  alarm(3);
  /* set handler for each sigaction struct */
  act.sa_handler = handler;
  sigint_act.sa_handler = sigIntHdl;
  sigusr1_act.sa_handler = sigusr1Hdl;
  /* checks if sigaction function works properly and exit if there is an error */
  if(sigaction(SIGALRM, &act, NULL) == -1){
    perror("Error");
    exit(1);
  }
  /* checks if sigaction function works properly, exit when error occurs */
  if(sigaction(SIGINT, &sigint_act, NULL) == -1){
    perror("Error");
    exit(1);
  }
  /* checks if sigaction function works properly, exit when error occurs */
  if(sigaction(SIGUSR1 , &sigusr1_act, NULL) == -1){
    perror("Error");
    exit(1);
  }
  /* run infinite loop */
  while(1){
  }
  /* return 0 when there are no errors */
  return 0;
}
