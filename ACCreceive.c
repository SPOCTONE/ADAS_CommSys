#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>

#define SIZE 512

typedef struct car {
  float speed;
  float distance;
} ACC;

int main() {
  printf("\nReceiver Function:\n");
  ACC receive;
  float speed, distance, threshold_distance = 100;
  int msgid = msgget((key_t)1, 0666 | IPC_CREAT);
  
  if((msgrcv(msgid, (void *)&receive, 0, 0, 0)) == -1) {
  perror("msgrcv");
  }
  
  speed = receive.speed;
  printf("The speed of our car is: %.2f kmph\n", speed);
  float threshold = 2*(speed/3.6); //atleast two seconds behind the vehicle in front
  printf("Minimum safe distance between two cars on a highway at this speed should be: %.2f metres\n", threshold);
  distance = receive.distance;
  printf("The distance between us and the car in front is: %.2f m\n", distance);
  
  if((msgctl(msgid, IPC_RMID, NULL)) == -1) {
  perror("msgctl");
  };
  
  if (distance >= threshold) {
    printf("\nWe will continue cruising at the same speed\n");
  } 
  else if (distance < threshold) {
    printf("\nWe will need to change the cruising speed in order to maintain a safe distance from the car in front\n");
  }
  execl("/home/sys1/Project/menu", "menu", NULL);
  return 0;
}
