#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <pthread.h>
#include <semaphore.h>

sem_t semaphore; // semaphore variale declaration in global space
int* flags; // declaring an integer pointer to store the flags 

void* BSD() {
	char choice;
	static int count = 0;
	
	sem_wait(&semaphore); // s=0
	
	printf("Is the camera %d detecting any vehicles? Press Yes (Y) or No (N)\n", ++count);
	scanf(" %c", &choice);
	if(choice== 'y' || choice== 'Y') {
		*flags=1;
		flags++;	
	}
	else {
		*flags=0;
		flags++;
	}
	
	sem_post(&semaphore); // ss=1
	
	if(count==3) {
		execl("/home/sys1/Project/BSDalert", "BSDalert", NULL);
	}
}

int main()
{	
	key_t key = ftok("shmfile", 13); // generating an IPC key
	int shmid = shmget(key, 64, 0666 | IPC_CREAT); 
	// allocating a shared memory segment and storing the identifier in shmid
	flags = shmat(shmid, 0, 0); 
	// attaching the shm segment associated with the shmid and returning it's starting address
	
	pthread_t cam1, cam2, cam3; //bs here refers to the different blind spots
	sem_init(&semaphore,0,1); //Binary semaphor
	
	pthread_create(&cam1, NULL, BSD, NULL);
	pthread_create(&cam2, NULL, BSD, NULL);
	pthread_create(&cam3, NULL, BSD, NULL);
	
	pthread_join(cam1, NULL);
	pthread_join(cam2, NULL);
	pthread_join(cam3, NULL);
	
	shmdt(flags);
	return 0;
}
