#include<stdio.h>
#include<sys/shm.h>
#include<unistd.h>

typedef struct collision {
  char f_cam;
  char b_cam;
  char l_cam;
  char r_cam;
  int f_dist;
  int b_dist;
  int l_dist;
  int r_dist;
  int speed;
} car;

int main() {
  int i = 0;
  key_t key = ftok("shmfile", 6597);
  int shmid = shmget(key, 1024, 0666 | IPC_CREAT);
  car *ptr = (car *)shmat(shmid, NULL, 0);
  int THRESHOLD_DISTANCE = 2*(ptr->speed/3.6);
  printf("\nThe Threshold distance is %d\n",THRESHOLD_DISTANCE);
  printf("\nData read from memory\n");

  printf("\nObstacle Detected by Camera %d (Front) : %c\n", ++i, ptr->f_cam);
  if (ptr->f_cam == 'y' || ptr->f_cam == 'Y') {
     printf("Distance: %d meters\n", ptr->f_dist);
     if(ptr->f_dist <= THRESHOLD_DISTANCE) {
      printf("Alert!! Collision may occur from your front\n");
     }
     else {
      printf("You're good to go\n");
     }
  }
   else {
      printf("You're good to go\n");
  }

  printf("\nObstacle Detected by Camera %d (Back) : %c\n", ++i, ptr->b_cam);
  if (ptr->b_cam == 'y' || ptr->b_cam == 'Y') {
    printf("Distance: %d meters\n", ptr->b_dist);
    if(ptr->b_dist <= THRESHOLD_DISTANCE) {
      printf("Alert!! Collision may occur from your Back\n");
    }
    else {
      printf("You're good to go\n");
    }
  }
   else {
      printf("You're good to go\n");
   }

  printf("\nObstacle Detected by Camera %d (Left): %c\n", ++i, ptr->l_cam);
  if (ptr->l_cam == 'y' || ptr->l_cam == 'Y') {
    printf("Distance: %d meters\n", ptr->l_dist);
    if(ptr->l_dist <= THRESHOLD_DISTANCE) {
      printf("Alert!! Collision may occur from your Left\n");
    }
    else {
      printf("You're good to go\n");
    }
  }
  else {
      printf("You're good to go\n");
  }

  printf("\nObstacle Detected by Camera %d (Right) : %c\n", ++i, ptr->r_cam);
  if (ptr->r_cam == 'y' || ptr->r_cam == 'Y') {
    printf("Distance : %d meters\n", ptr->r_dist);
    if(ptr->r_dist <= THRESHOLD_DISTANCE) {
      printf("Alert!! Collision may occur from your Right\n");
    }
    else {
      printf("You're good to go\n");
    }
  }
  else {
      printf("You're good to go\n");
  }

  shmdt(ptr);
  shmctl(shmid, IPC_RMID, NULL);
  
  return 0;
}
