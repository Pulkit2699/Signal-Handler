//////////////////////////////////////////////////////////////////////////////////
//
// Copyright 2019 Jim Skrentny
// Posting or sharing this file is prohibited, including any changes/additions.
//
///////////////////////////////////////////////////////////////////////////////
// Main File:        division.c
// This File:        division.c
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
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
/* counts number of successful divisions */
int counter;

/* This function handles floating point error signal  
 *
 * sig  signal number 
 * 
 */
void sgfpeHdl(int sig){
  /* print number of SIGFPE signals recieved and exit gracefully */
  printf("Error: a division by 0 operation was attempted.\n");
  printf("Total number of operations completed successfully: %d", counter);
  printf("\nThe program will be terminated.\n");
  exit(0);
}

/* This function handles SIGINT signals 
 *
 * sig  signal number 
 * 
 */
void sigintHdl(int sig){
 /* print number of SIGFPE signals recieved and exit gracefully */
 printf("\nTotal number of operations successfully completed: %d", counter);
 printf("\nThe program will be terminated.\n");
 exit(0);
}

/* This function calls signal handler to handle appropriate signal  
 *
 * returns 1 if an error occurs or 0 if everything works 
 */
int main(){
  /* set counter to 0 */
  counter = 0;
  /* create two sigaction structs to handle the right signals */
  struct sigaction act;
  struct sigaction sigint_act;
  /* reset all three sigaction structs */
  memset(&act, 0, sizeof(act));
  memset(&sigint_act, 0, sizeof(sigint_act));
  /* set handler for each sigaction struct */
  act.sa_handler = sgfpeHdl;
  sigint_act.sa_handler = sigintHdl;
  /* checks if sigaction function works properly and exit if there is an error */
  if(sigaction(SIGFPE, &act, NULL) == -1){
    perror("Error");
    exit(1);
  }
  /* checks if sigaction function works properly and exit if there is an error */
  if(sigaction(SIGINT, &sigint_act, NULL) == -1){
    perror("Error");
    exit(1);
  }
  
  while(1){
    /* buffer saves first and second integer */
    char buffer[100];
    /* prompt user for first and second integer */
    printf("Enter first integer: ");
    fgets(buffer, 100, stdin);
    /* save first integer entered by user */
    int firstNum = atoi(buffer);
    /* prompt user for first and second integer */
    printf("Enter second integer: ");
    fgets(buffer, 100, stdin);
    /* save second integer entered by user */
    int secondNum = atoi(buffer);
    /* calculate remainder and dividend */
    int divide = firstNum / secondNum;
    int remainder = firstNum % secondNum;
    /* print remainder and dividend and number of divisions */
    printf("%d / %d is %d with a remainder of %d\n", firstNum, secondNum, divide, remainder);
    /* increment counter */
    counter++;  
  }
  /* return 0 when there are no errors */
  return 0;
}
