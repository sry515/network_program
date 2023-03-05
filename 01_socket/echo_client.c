#include "../tools/tools.h"

#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>

#define BUF_SIZE 1024

int main(int argc, char **argv) {
  if (3 != argc) {
    printf("Usage: %s <ip> <port>", argv[0]);
    return -1;
  }

  struct sockaddr_in addr;
  memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = inet_addr(argv[1]);
  addr.sin_port = htons(atoi(argv[2]));

  int sock = socket(PF_INET, SOCK_STREAM, 0);
  if (-1 == sock) {
    error_handling("create socket error");
  }

  if (-1 == connect(sock, (struct sockaddr *)&addr, sizeof(addr))) {
    error_handling("connect error!");
  }
  printf("Connected......\n");

  char message[BUF_SIZE];
  while(1) {
    fputs("Input message(Q to quit): ", stdout);
    fgets(message, BUF_SIZE, stdin);

    if (!strcmp(message, "q\n") || !strcmp(message, "Q\n")) {
      break;
    }

    int write_len = strlen(message);
    write(sock, message, write_len);

    int read_len = 0;
    printf("Message from server: ");
    while (read_len < write_len) {
      int str_len = read(sock, message, BUF_SIZE-1);
      message[str_len] = 0;
      read_len += str_len;
      printf("%s", message);
    }
  }

  close(sock);
  return 0;
}