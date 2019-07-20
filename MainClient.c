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
  int sock = 0, valread; 
  struct sockaddr_in serv_addr; 
  char * msg = argv[1]; 
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
  send(sock, msg, strlen(msg) , 0 ); 
  printf("Sent: %s\n", msg); 
  valread = read( sock , buffer, 1024); 
  printf("Received: %s\n",buffer ); 
  printf("Info: Done!\n"); fflush(stdout);
}
