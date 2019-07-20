#include <stddef.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define HOST "127.0.0.1"
#define PORT 8080

int main(int argc, char * argv[]) {
  /* int c, sockfd; */
  /* struct sockaddr_in serv_addr; */
  /* struct in_addr addr; */

  /* //  addr.s_addr = inet_addr(HOST); */

  /* serv_addr.sin_family = AF_INET; */
  /* serv_addr.sin_port = htons(PORT); */
  /* //sockaddr.sin_addr = addr; */
  /* inet_pton(AF_INET, HOST, &serv_addr.sin_addr); */

  /* if (sockfd = socket(AF_INET, SOCK_STREAM, 0) < 0) { */
  /*   printf("Could not open socket\n"); fflush(stdout);     */
  /* }; */

  /* if (connect(sockfd,(struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) { */
  /*   printf("Could not connect to server\n"); fflush(stdout);         */
  /* } */

  /* shutdown(sockfd, 2); */

  int sock = 0, valread; 
  struct sockaddr_in serv_addr; 
  char *hello = "Hello from client"; 
  char buffer[1024] = {0}; 
  if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    { 
      printf("Error: Socket creation error \n"); 
      return -1; 
    } 
   
  serv_addr.sin_family = AF_INET; 
  serv_addr.sin_port = htons(PORT); 
       
  // Convert IPv4 and IPv6 addresses from text to binary form 
  if(inet_pton(AF_INET, HOST, &serv_addr.sin_addr)<=0)  
    { 
      printf("Error: Invalid address/ Address not supported \n"); 
      return -1; 
    } 
   
  if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
    { 
      printf("Error: Connection Failed \n"); 
      return -1; 
    } 
  send(sock , hello , strlen(hello) , 0 ); 
  printf("Log: Hello message sent\n"); 
  valread = read( sock , buffer, 1024); 
  printf("%s\n",buffer ); 
  printf("Log: Done!\n"); fflush(stdout);
}
