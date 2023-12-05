#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {

  char buffer[1024];
  char *ip = "127.0.0.1"; // local host ip
  int port = 8080; 
  
  struct sockaddr_in addr;
  socklen_t addr_size = sizeof(addr);
  int sockfd = socket(AF_INET, SOCK_DGRAM, 0);

  memset(&addr, '\0', addr_size); // clearing the memory space of the variable addr
  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);
  addr.sin_addr.s_addr = inet_addr(ip);

  
  bzero(buffer, 1024);// Erasing 1024 bytes before using the buffer

  strcpy(buffer, "Hi from the UDP Client");
  sendto(sockfd, buffer, 1024, 0, (struct sockaddr*)&addr, addr_size);
  printf("[+]Data sent: %s\n", buffer);


  bzero(buffer, 1024);
  addr_size = sizeof(addr);
  recvfrom(sockfd, buffer, 1024, 0, (struct sockaddr*)&addr, &addr_size);
  printf("[+]Data received: %s\n", buffer);
  
  bzero(buffer, 1024);

  recvfrom(sockfd, buffer, 1024, 0, (struct sockaddr *)&addr, &addr_size);
  printf("[+]Data received: %s\n", buffer);
  double speed = atof(buffer);
  
  printf("\nThe speed of the car is: %.4lf kmph\n", speed);
  printf("Initiating Emergency Breaking.\n");
  printf("Reducing the speed by 15 feet/s (maximum safe deceleration of a typical car)\n");
  while(speed>0) { //
    sleep(1);
    speed=speed-16.4592;
    if(speed<0) {
    printf("0\n\n");
    continue;
    }
    printf("%.4lf\n", speed);
  }
  
  return 0;
}