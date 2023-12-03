#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void lane_deviation(int signo) {
  if (signo == SIGINT) {
    printf("\nALERT! lane deviation detected.\n");
    execl("/home/sys1/Project/menu", "menu", NULL);
    exit(EXIT_SUCCESS);
  } 
  else if(signo == SIGQUIT) {
    printf("\nNo lane change observed.\n");
    execl("/home/sys1/Project/menu", "menu", NULL);
    exit(EXIT_SUCCESS);
    }
  }

int main() {
    printf("Are you cruising in your lane?\n");
    printf("press Control-C if you are deviating from the lane or Control-\\ if you're not.\n");
    signal (SIGINT, lane_deviation);
    signal (SIGQUIT, lane_deviation);
    
    if (signal(SIGINT, lane_deviation) == SIG_ERR) {
      fprintf(stderr, "cannot handle SIGINT!\n");
      exit(EXIT_FAILURE);
    }
    if (signal(SIGQUIT, lane_deviation) == SIG_ERR) {
      fprintf(stderr, "cannot handle SIGQUIT!\n");
      exit(EXIT_FAILURE);
    }
    
    while(1);
    return 0;
}
