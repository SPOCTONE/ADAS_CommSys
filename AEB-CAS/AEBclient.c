#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define PORT 4444

int main() {
  
  float speed;
  int clientSocket;
  struct sockaddr_in serverAddr;
  
  clientSocket = socket(PF_INET, SOCK_STREAM, 0);
  printf("[+]Client Socket Created Sucessfully.\n");

  memset(&serverAddr, '\0', sizeof(serverAddr));
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(PORT);
  serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

  connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
  printf("[+]Connected to Server.\n\n");

  recv(clientSocket, &speed, 1024, 0);

  printf("The speed of the car is: %.4f kmph\n", speed);
  printf("Initiating Emergency Breaking.\n");
  printf("Reducing the speed by 15 feet/s (maximum safe deceleration of a typical car)\n");
  while (speed > 0) {
    sleep(1);
    speed = speed - 16.4592;
    if (speed < 0) {
      printf("0\n");
      continue;
    }
    printf("%.4f\n", speed);
  }
  printf("The car has been stopped safely.\n");
  printf("\n[+]Closing the connection.\n");

  execl("/home/sys1/Project/menu", "menu", NULL);
  return 0;
}
