#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

// function to handle lane deviation signals
void laneDeviation(int signo) {
  if (signo == SIGINT) {
    printf("\nALERT! lane deviation detected.\n"); 
    // printing alert message for lane deviation
    execl("/home/sys1/Project/menu", "menu", NULL);
    exit(EXIT_SUCCESS); //exits with success status
  } else if (signo == SIGQUIT) {
    printf("\nNo lane change observed.\n");
    // printing message in case of no lane change
    execl("/home/sys1/Project/menu", "menu", NULL);
    exit(EXIT_SUCCESS);
  }
}

int main() {
  printf("Are you cruising in your lane?\n"); 
  printf("press Control-C if you are deviating from the lane or Control-\\ if you're not.\n");
  // displaying instructions for signaling lane deviation

  // setting up signal handler SIGINT and SIGQUIT
  signal(SIGINT, laneDeviation);
  // SIGINT signal handler represents interrupt signal when user presses ctrl-c
  signal(SIGQUIT, laneDeviation);
  // SIGQUIT signal handler represents quit signal when user presses ctrl-\
  
  // checking for errors in setting up SIGNT handler
  if (signal(SIGINT, laneDeviation) == SIG_ERR) {
    fprintf(stderr, "cannot handle SIGINT!\n");
    exit(EXIT_FAILURE);
  }

  // checking for errors in setting up SIGQUIT handler
  if (signal(SIGQUIT, laneDeviation) == SIG_ERR) {
    fprintf(stderr, "cannot handle SIGQUIT!\n");
    exit(EXIT_FAILURE);
  }

  while (1);
  return 0;
}
