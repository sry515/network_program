#include "../tools/tools.h"

#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc, char **argv) {
  if (3 != argc) {
    printf("Usage: %s <ip> <port>", argv[0]);
    return -1;
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
  if (-1 == connect(sock, (struct sockaddr *)&addr, sizeof(addr))) {
    error_handling("connect error!");
  }

  int idx = 0;
  int str_len = 0;
  int read_len = 0;
  char message[30];

  while (0 != (read_len = read(sock, &message[idx++], 1))) {
    if (-1 == read_len) {
      error_handling("read() error!");
    }

    str_len += read_len;
  } 
  printf("Message from server: %s \n", message);
  printf("call read count: %d \n", str_len);

  close(sock);
  return 0;
}