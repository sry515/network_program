#include "../tools/tools.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>


int main(int argc, char **argv) {
  if (argc != 2) {
    printf("Usage: %s <port>", argv[0]);
    exit(1);
  }

  int serv_sock = socket(PF_INET, SOCK_STREAM, 0);
  if (-1 == serv_sock) {
    error_handling("create socket error!");
  }

  struct sockaddr_in serv_addr;
  memset(&serv_addr, 0, sizeof(serv_addr));
  serv_addr.sin_family = PF_INET;
  serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  serv_addr.sin_port = htons(atoi(argv[1]));
  if (-1 == bind(serv_sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr))) {
    error_handling("bind ip and port error!");
  }

  if (-1 == listen(serv_sock, 5)) {
    error_handling( "start listen status error!");
  }

  int clnt_sock;
  struct sockaddr_in clnt_addr;
  socklen_t clnt_addr_sz = sizeof(clnt_addr);
  clnt_sock = accept(serv_sock, (struct sockaddr *) &clnt_addr, &clnt_addr_sz);
  if (-1 == clnt_sock) {
    error_handling("accept connect error!");
  }

  char message[] = "Hello world!";
  write(clnt_sock, message, sizeof(message));
  close(clnt_sock);
  close(serv_sock);
  
  return 0;
}