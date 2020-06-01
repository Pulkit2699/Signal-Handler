//////////////////////////////////////////////////////////////////////////////////
//
// Copyright 2019 Jim Skrentny
// Posting or sharing this file is prohibited, including any changes/additions.
//
///////////////////////////////////////////////////////////////////////////////
// Main File:        sendsig.c
// This File:        sendsig.c
// Other Files:      (name of all other files if any)
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
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <error.h>
#include <signal.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>

/* This function gets input from command line arguments and sends a signal with kill method 
 *
 * argc the number of arguments in the command line 
 * argv an array to access command line arguments passed into by user 
 * returns 0 if everything runs successfully and 1 if errors are present 
 */

int main(int argc, char* argv[]){
  /* process id of a program*/
  int pid;
  /* get process id from command line argument at index 2*/
  pid = atoi(argv[2]);
  
  /* make sure user enters 3 command line arguments */
  if(argc == 3){
     /* kill process and send SIGUSR1 signal */
     if(strcmp(argv[1], "-u") == 0 ){
     /* check if kill works properly */
      if(kill(pid,SIGUSR1) == -1){
        perror("Error");
	exit(1);
      }
     }
     /* kill process and send SIGINT SIGNAL */
     if(strcmp(argv[1], "-i") == 0){
      /* check if kill works properly */
       if(kill(pid, SIGINT) == -1){
         perror("Error");
	 exit(1);
       }
     }
  
  } else{
      /* print message since user did not enter correct amount of command line arguments */
     printf("Usage: <signal type> <pid>\n");
  }
  
}
