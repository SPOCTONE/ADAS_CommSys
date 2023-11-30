#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <pthread.h>
#include <semaphore.h>

sem_t semaphore; // semaphore variale declaration in global space
int* temp; // declaring an integer pointer to store the flags 

void* foobar() {
	char c;
	static int i = 0;
	
	sem_wait(&semaphore); // s=0
	
	printf("Is the camera %d detecting any vehicles? Press Yes (Y) or No (N)\n", ++i);
	scanf(" %c", &c);
	if(c== 'y' || c == 'Y') {
		*temp=1;
		temp++;	
	}
	else {
		*temp=0;
		temp++;
	}
	
	sem_post(&semaphore); // ss=1
	
	if(i==3) {
		execl("/home/sys1/Project/BSDalert", "BSDalert", NULL);
	}
}

int main()
{	
	key_t key = ftok("shmfile", 13); // generating an IPC key
	int shmid = shmget(key, 64, 0666 | IPC_CREAT); 
	// allocating a shared memory segment and storing the identifier in shmid
	temp = shmat(shmid, 0, 0); 
	// attaching the shm segment associated with the shmid and returning it's starting address
	
	pthread_t cam1, cam2, cam3; //bs here refers to the different blind spots
	sem_init(&semaphore,0,1); //Binary semaphor
	
	pthread_create(&cam1, NULL, foobar, NULL);
	pthread_create(&cam2, NULL, foobar, NULL);
	pthread_create(&cam3, NULL, foobar, NULL);
	
	pthread_exit(NULL);
	shmdt(temp);
	return 0;
}
