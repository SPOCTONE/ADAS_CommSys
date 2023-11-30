#include <stdio.h>
#include <sys/shm.h>

int* temp;

int main() {
	key_t key = ftok("shmfile", 13); // generating an IPC key
	int shmid = shmget(key, 64, 0666 | IPC_CREAT); // allocating a shared memory segment and storing the identifier in shmid
	temp = shmat(shmid, 0, 0); // attaching the shm segment associated with the shmid and returning it's starting address
	printf("\nStatus of:\ncamera 1 at the back of our car: %s\ncamera 2 on the left side of our car: %s\ncamera 3 on the right side of our car: %s\n\n", temp[0] ? "Vehicle detected!" : "No Vehicle detected.", temp[1] ? "Vehicle detected!" : "No Vehicle detected.", temp[2] ? "Vehicle detected!" : "No Vehicle detected.");
	// temp[0] refers to the status of the first camera at the back of our car
	// temp[1] refers to the status of the second camera on the left side of our car
	// temp[2] refers to the status of the third camera on the right side of our car
	
	if(temp[0] == 0 && temp[1] == 0 && temp[2] == 0) {
		printf("There are no vehicles in any of our blind spots\n");
	}
	else if(temp[0] == 0 && temp[1] == 0 && temp[2] == 1) {
		printf("There are vehicle(s) to the right of our car\n");
	}
	else if(temp[0] == 0 && temp[1] == 1 && temp[2] == 0) {
		printf("There are vehicle(s) to the left of our car\n");
	}
	else if(temp[0] == 1 && temp[1] == 0 && temp[2] == 0) {
		printf("There are vehicle(s) behind our car\n");
	}
	else if(temp[0] == 0 && temp[1] == 1 && temp[2] == 1) {
		printf("There are vehicle(s) on both the sides of our car\n");
	}
	else if(temp[0] == 1 && temp[1] == 1 && temp[2] == 0) {
		printf("There are vehicle(s) behind our car on the left\n");
	}
	else if(temp[0] == 1 && temp[1] == 0 && temp[2] == 1) {
		printf("There are vehicle(s) behind our car on the right\n");
	}
	else {
		printf("There are vehicle(s) behind our car as well as on both the sides\n");
	}
	
	shmdt(temp);
	shmctl(shmid, IPC_RMID, NULL);
return 0;
}
