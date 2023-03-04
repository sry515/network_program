
#include <sys/socket.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
  int fd_1, fd_2, fd_3;
  fd_1 = socket(PF_INET, SOCK_STREAM, 0);
  fd_2 = open("test.txt", O_CREAT | O_WRONLY | O_APPEND);
  fd_3 = socket(PF_INET, SOCK_DGRAM, 0);

  printf("fd 1 : %d \n", fd_1);
  printf("fd 2 : %d \n", fd_2);
  printf("fd 3 : %d \n", fd_3);

  close(1);
  close(2);
  close(3);

  return 0;
}