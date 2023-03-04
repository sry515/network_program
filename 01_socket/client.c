#include "../tools/tools.h"

#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

int main(int argc, char **argv) {
  if (3 != argc) {
    printf("Usage: %s <ip> <port>", argv[0]);
    exit(1);
  }

  int sock = socket(PF_INET, SOCK_STREAM, 0);
  if (-1 == sock) {
    error_handling("create socket error!");
  }

  struct sockaddr_in addr;
  memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = inet_addr(argv[1]);
  addr.sin_port = htons(atoi(argv[2]));
  if (-1 == connect(sock, (struct sockaddr *) &addr, sizeof(addr))) {
    error_handling("connect error!");
  }

  char message[30];
  int str_len = read(sock, message, sizeof(message)-1);
  if (-1 == str_len) {
    error_handling("read message error!");
  }

  printf("message from server: %s\n", message);
  close(sock);

  return 0;
}