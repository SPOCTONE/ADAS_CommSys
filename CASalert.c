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
  uint32_t shmid = shmget(key, 1024, 0666 | IPC_CREAT);
  car *receive = (car *)shmat(shmid, NULL, 0);

  printf("Data read from shared memory\n");

  char *camDir[] = {"front", "left", "right", "back"};

  if (receive->choice == 'y' || receive->choice == 'Y') {

    float thresholdDistance = 2 * (receive->speed / 3.6);
    printf("\nThreshold distance is %.2f meters\n", thresholdDistance);

    for (uint8_t i = 0; i < 4; i++) {

      if (receive->camNum[i] == 1) {
        printf("Distance from camera %d at the %s: %.2f meters\n", i + 1, camDir[i], receive->distance[i]);

        if ((receive->distance[i] < thresholdDistance) && i!=3) {
          printf("Alert! Collision may occur in the field of view of camera %d at the %s\n", i + 1, camDir[i]);
          execl("/home/sys1/Project/AEBclient", "AEBclient", NULL);
        } 
        else if((receive->distance[i] < thresholdDistance) && i==3) {
          printf("Alert! Collision may occur in the field of view of camera %d at the %s\n", i + 1, camDir[i]);
        } 
        else {
          printf("You're good to go\n");
        }
      }
    }
  } 
  else {
    printf("You're good to go\n");
    execl("/home/sys1/Project/menu", "menu", NULL);
  }

  shmdt(receive);
  return 0;
}