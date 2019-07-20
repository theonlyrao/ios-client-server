#include <arpa/inet.h>
#include <stddef.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <ctype.h>

#define HOST "127.0.0.1"
#define PORT 8080

int main(int argc, char * argv[]) {
  int sockfd, newsockfd, clilen, childpid, valread;
  struct sockaddr_in cli_addr, serv_addr;
  char buffer[1024] = {0};

  if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
      printf("Error: Could not open socket\n"); fflush(stdout);          
  }

  bzero((char *) &serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  serv_addr.sin_port = htons(PORT);

  if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
    printf("Info: Could not bind local address\n"); fflush(stdout);          
  }

  listen(sockfd, 5);

  for ( ; ; ) {
    clilen = sizeof(cli_addr);
    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);

    if (newsockfd < 0) {
      printf("Error: Server accept error\n"); fflush(stdout);
    } else if (newsockfd >= 0) {
      printf("Info: Made connection\n"); fflush(stdout);            
    }

    valread = read(newsockfd, buffer, sizeof(buffer));
    printf("Received: %s\n",buffer);

    for (int i = 0; i < strlen(buffer); i++) {
      buffer[i] = toupper(buffer[i]);
    }
    
    send(newsockfd, buffer, sizeof(buffer), 0);
    printf("Sent: %s\n",buffer);    
  }

  shutdown(newsockfd, 2);  
  printf("Info: Done!\n"); fflush(stdout);
}
