#include "../tools/tools.h"
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

#define BUF_SIZE 10

int main(int argc, char **argv) {
  if (argc != 2) {
    printf("Usage: %s <port>\n", argv[0]);
    return -1;
  }

  struct sockaddr_in serv_addr;
  memset(&serv_addr, 0, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  serv_addr.sin_port = htons(atoi(argv[1]));

  int serv_sock = socket(PF_INET, SOCK_STREAM, 0);
  if (-1 == serv_sock) {
    error_handling("create serv socket error!");
  }

  if (-1 == bind(serv_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr))) {
    error_handling("bind ip and port error!");
  }

  if (-1 == listen(serv_sock, 5)) {
    error_handling("start listen status error!");
  }

  struct sockaddr_in clnt_addr;
  socklen_t clnt_addr_sz = sizeof(clnt_addr);

  for (int i = 0; i < 5; ++i) {
    int clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_addr, &clnt_addr_sz);
    if (-1 == clnt_sock) {
      error_handling("accept connect error!");
    } else {
      printf("Connect client: %d\n", i+1);
    }

    char message[BUF_SIZE];
    int str_len;
    while (0 != (str_len = read(clnt_sock, message, BUF_SIZE))) {
      write(clnt_sock, message, str_len);
    }

    close(clnt_sock);
    
  }
  
  close(serv_sock);
  return 0;
}