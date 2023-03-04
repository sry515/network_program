#include "../tools/tools.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
  int fd;
  char buf[] = "Hello world!\n";
  fd = open("data.txt", O_CREAT | O_WRONLY | O_TRUNC);
  if (-1 == fd) {
    error_handling("open file error");
  }

  printf("file description: %d \n", fd);

  if (-1 == write(fd, buf, sizeof(buf))) {
    error_handling("write ./data.txt error");
  }
  close(fd);

  return 0;
}