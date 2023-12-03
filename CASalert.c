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
  key_t key = ftok("shmfile", 6597);
  int shmid = shmget(key, 1024, 0666 | IPC_CREAT);
  car *ptr = (car *)shmat(shmid, NULL, 0);

  printf("Data read from shared memory\n");

  char *camDir[] = {"front", "left", "right", "front"};
  if (ptr->choice == 'y' || ptr->choice == 'Y') {
    float thresholdDistance = 2 * (ptr->speed / 3.6);
    printf("\nThreshold distance is %.2f meters\n", thresholdDistance);
    for (int i = 0; i < 4; i++) {
      if (ptr->camNum[i] == 1) {
        printf("Distance from camera %d at the %s: %.2f meters\n", i + 1, camDir[i], ptr->dist[i]);
        if (ptr->dist[i] < thresholdDistance) {
          printf("Alert! Collision may occur in the field of view of camera %d at the %s\n", i + 1, camDir[i]);
          execl("/home/sys1/Project/AEBclient", "AEBclient", NULL);
        } else {
          printf("You're good to go\n");
        }
      }
    }
  } else {
    printf("You're good to go\n");
    execl("/home/sys1/Project/menu", "menu", NULL);
  }

  shmdt(ptr);
  return 0;
}

