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
  int i=0;
  key_t key=ftok("shmfile",6597);
  int shmid=shmget(key,1024,0666|IPC_CREAT);
  car *ptr=(car*)shmat(shmid,NULL,0);

  printf("Enter the speed of the car: ");
  scanf("%d", &ptr->speed);

  printf("Is the camera %d (Front) detecting any obstacle? Press Yes (Y) or No (N)\n", ++i);
  scanf(" %c",&ptr->f_cam);
  if(ptr->f_cam == 'y' || ptr->f_cam == 'Y') {
    printf("Enter the distance of the obstacle from the front camera: ");
    scanf("%d",&ptr->f_dist);
  }

  printf("Is the camera %d (Back) detecting any obstacle? Press Yes (Y) or No (N)\n", ++i);
  scanf(" %c",&ptr->b_cam);
  if(ptr->b_cam == 'y' || ptr->b_cam == 'Y') {
    printf("Enter the distance of the obstacle from the back camera: ");
    scanf("%d",&ptr->b_dist);
  }

  printf("Is the camera %d (Left) detecting any obstacle? Press Yes (Y) or No (N)\n", ++i);
  scanf(" %c",&ptr->l_cam);
  if(ptr->l_cam == 'y' || ptr->l_cam == 'Y') {
    printf("Enter the distance of the obstacle from the back camera: ");
    scanf("%d",&ptr->l_dist);
  }

  printf("Is the camera %d (Right) detecting any obstacle? Press Yes (Y) or No (N)\n", ++i);
  scanf(" %c",&ptr->r_cam);
  if(ptr->r_cam == 'y' || ptr->r_cam == 'Y') {
    printf("Enter the distance of the obstacle? from the back camera: ");
    scanf("%d",&ptr->r_dist);
  }

  printf("\nData shared successfully\n");
  shmdt(ptr);

  execl("/home/sys1/Project/CASalert","CASalert",NULL);
  return 0;
}
