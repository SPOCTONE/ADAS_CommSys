#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define PORT 4444

typedef struct collision {
  char choice;
  int camNum[4];
  float dist[4];
  float speed;
} car;

int main() {

  key_t key = ftok("shmfile", 13);
  int shmid = shmget(key, 1024, 0666 | IPC_CREAT);
  car *ptr = (car *)shmat(shmid, NULL, 0);

  int serverSocket;
  struct sockaddr_in serverAddr;

  int newSocket;
  struct sockaddr_in newAddr;

  socklen_t addr_size;

  serverSocket = socket(AF_INET, SOCK_STREAM, 0);
  printf("[+]Server Socket Created Sucessfully.\n");

  memset(&serverAddr, '\0', sizeof(serverAddr));
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(PORT);
  serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

  bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
  printf("[+]Bind to Port number %d.\n", 4444);

  listen(serverSocket, 5);
  printf("[+]Listening...\n");
  
  newSocket = accept(serverSocket, (struct sockaddr *)&newAddr, &addr_size);
  
  send(newSocket, &ptr->speed, sizeof(ptr->speed), 0);
  // passing the value which is received from CAS via shared memory.
  
  printf("\n[+]Closing the connection.\n");
  shmctl(shmid, IPC_RMID, NULL);
  shmdt(ptr);
  return 0;
}
