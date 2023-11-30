#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>

#define SIZE 512

typedef struct car {
  char foo[SIZE];
  float speed;
  float distance;
} ACC;

int main() {
  printf("\nReceiver Function:\n");
  ACC c2;
  char buf[SIZE];
  float speed, distance, threshold_distance = 100;
  int msgid = msgget((key_t)1, 0666 | IPC_CREAT);
  
  msgrcv(msgid, (void *)&c2, SIZE, 0, 0);
  strcpy(buf,c2.foo);
  speed = c2.speed;
  printf("The speed of our car is: %.2f kmph\n", speed);
  float threshold = 2*(speed/3.6); //atleast two seconds behind the vehicle in front
  printf("Minimum safe distance between two cars on a highway at this speed should be: %.2f metres\n", threshold);
  distance = c2.distance;
  printf("The distance between us and the car in front is: %.2f m\n", distance);
  msgctl(msgid, IPC_RMID, NULL);
  
  if (distance > threshold) {
    printf("\nWe will continue cruising at the same speed\n");
  } 
  else if (distance < threshold) {
    printf("\nWe will need to change the cruising speed in order to maintain a safe distance from the car in front\n");
  }
  
  return 0;
}
