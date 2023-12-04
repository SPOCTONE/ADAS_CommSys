#include <stdio.h>
#include <stdint.h>
#include <sys/shm.h>
#include <unistd.h>

typedef struct collision {
  char choice;
  uint8_t camNum[4];
  float distance[4];
  float speed;
} car;

int main() {

  key_t key = ftok("shmfile", 13);
  uint8_t shmid = shmget(key, 1024, 0666 | IPC_CREAT);
  car *sender = (car *)shmat(shmid, NULL, 0);
  
  printf("Enter the speed of the car : ");
  scanf("%f", &sender->speed);
  
  printf("Are the cameras detecting any obstacle? Press Yes (Y) or No (N): ");
  scanf(" %c", &sender->choice);
  
  char *camDir[] = {"front", "left", "right", "back"};
  
  if (sender->choice == 'Y' || sender->choice == 'y') {
    for (int i = 0; i < 4; i++) {
      printf("Enter 1 if the camera %d at the %s is detecting an obstacle, 0 if not : ", i + 1, camDir[i]);
      scanf("%hhu", &sender->camNum[i]);
    }

    for (int i = 0; i < 4; i++) {
      if (sender->camNum[i] == 1) {
        printf("Enter the distance between the camera %d at the %s and the obstacle : ", i + 1, camDir[i]);
        scanf("%f", &sender->distance[i]);
      }
    }
  }
  printf("\nData shared successfully\n");
  shmdt(sender);
  execl("/home/sys1/Project/CASalert", "CASalert", NULL);
  return 0;
}