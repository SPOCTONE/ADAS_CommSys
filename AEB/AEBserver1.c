#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>

#define PORT 4444

int main() {

  int serverSocket;
  struct sockaddr_in serverAddr;

  int newSocket;
  struct sockaddr_in newAddr;

  socklen_t addr_size;
  char buffer[1024];

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

  printf("\nEnter the current speed of the vehicle (in kmph): ");
  scanf("%s", buffer);

  send(newSocket, buffer, strlen(buffer), 0);

  printf("\n[+]Closing the connection.\n");
  return 0;
}
