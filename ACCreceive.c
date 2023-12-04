#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>

typedef struct car {
  float speed;
  float distance;
} ACC;

int main() {
  int msgid; //message queue id
  ACC receive; //structure variable containing the speed and distance of our car to be received as a message
  printf("\nReceiver Function:\n");

  if (msgid = msgget((key_t)13, 0666 | IPC_CREAT) == -1) { // create message queue
    perror("msgsnd");
  }
  
  if((msgrcv(msgid, (void *)&receive, 0, 0, 0)) == -1) { // receive message from the queue
  perror("msgrcv");
  }
  
  printf("The speed of our car is: %.2f kmph\n", receive.speed);
  float threshold = 2*(receive.speed/3.6); //atleast two seconds behind the vehicle in front
  printf("Minimum safe distance between two cars on a highway at this speed should be: %.2f metres\n", threshold);
  printf("The distance between us and the car in front is: %.2f m\n", receive.distance);
  
  if((msgctl(msgid, IPC_RMID, NULL)) == -1) { // delete message queue
  perror("msgctl");
  };
  
  if (receive.distance >= threshold) {
    printf("\nWe will continue cruising at the same speed\n");
  } 
  else {
    printf("\nWe will need to change the cruising speed in order to maintain a safe distance from the car in front\n");
  }
  
  // execl("/home/sys1/Project/menu", "menu", NULL);
  return 0;
}
