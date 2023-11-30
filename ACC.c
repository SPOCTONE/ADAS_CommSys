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

int main(int argc, char *argv[]) {

  printf("Sender Function:\n");
  ACC c1;
  int msgid;
  char bar[SIZE] = "foobar";
  float threshold_distance = 100;
  
  msgid = msgget((key_t)1, 0666 | IPC_CREAT);
  if (msgid == -1) // -1 means message queue not creating
  {
    printf("\nError in creating mesage queue\n");
    exit(0);
  }
  
  strcpy(c1.foo, bar);
  printf("Enter the current speed of our car (in kmph):\n");
  scanf("%f", &c1.speed);

  printf("Enter the distance between us and the car in front (in metres) :\n");
  scanf("%f", &c1.distance);
  
  if (msgsnd(msgid, (void *)&c1, SIZE, 0) == -1) {
    printf("\nMessage not sent\n");
  }
  
  execl("/home/sys1/Project/ACCreceive", "ACCreceive", NULL);
  return 0;
}
  
