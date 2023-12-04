#include <stdio.h>
#include <sys/shm.h>
#include <unistd.h>

typedef struct collision {
  char choice;
  int camNum[4];
  float dist[4];
  float speed;
} car;

int main() {

  int i = 0;
  key_t key = ftok("shmfile", 13);
  int shmid = shmget(key, 1024, 0666 | IPC_CREAT);
  car *ptr = (car *)shmat(shmid, NULL, 0);
  
  printf("Enter the speed of the car : ");
  scanf("%f", &ptr->speed);
  
  printf("Are the cameras detecting any obstacle? Press Yes (Y) or No (N): ");
  scanf(" %c", &ptr->choice);
  
  char *camDir[] = {"front", "left", "right", "back"};
  
  if (ptr->choice == 'Y' || ptr->choice == 'y') {
    for (int i = 0; i < 4; i++) {
      printf("Enter 1 if the camera %d at the %s is detecting an obstacle, 0 if not : ", i + 1, camDir[i]);
      scanf("%d", &ptr->camNum[i]);
    }

    for (int i = 0; i < 4; i++) {
      if (ptr->camNum[i] == 1) {
        printf("Enter the distance between the camera %d at the %s and the obstacle : ", i + 1, camDir[i]);
        scanf("%f", &ptr->dist[i]);
      }
    }
  }
  printf("\nData shared successfully\n");
  shmdt(ptr);
  execl("/home/sys1/Project/CASalert", "CASalert", NULL);
  return 0;
}