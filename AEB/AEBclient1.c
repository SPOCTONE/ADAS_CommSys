#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>

#define PORT 4444

int main() {

  int clientSocket;
  struct sockaddr_in serverAddr;
  char buffer[1024];

  clientSocket = socket(PF_INET, SOCK_STREAM, 0);
  printf("[+]Client Socket Created Sucessfully.\n");

  memset(&serverAddr, '\0', sizeof(serverAddr));
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(PORT);
  serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

  connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
  printf("[+]Connected to Server.\n\n");

  recv(clientSocket, buffer, 1024, 0);
  double speed = atof(buffer);
  printf("The speed of the car is: %.4lf kmph\n", speed);
  printf("Initiating Emergency Breaking.\n");
  printf("Reducing the speed by 15 feet/s (maximum safe deceleration of a typical car)\n");
  while(speed>0) {
    sleep(1);
    speed=speed-16.4592;
    if(speed<0) {
    printf("0\n");
    continue;
    }
    printf("%.4lf\n", speed);
  }
  printf("The car has been stopped safely.\n");
  printf("\n[+]Closing the connection.\n");
  return 0;
}
