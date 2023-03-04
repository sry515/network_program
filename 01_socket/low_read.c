#include "../tools/tools.h"

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define BUF_SIZE 100

int main() {
  int fd;
  fd = open("data.txt", O_RDONLY);
  if (-1 == fd) {
    error_handling("open ./data.txt error!");
  }

  printf("file description: %d \n", fd);

  char buf[BUF_SIZE];
  if (-1 == read(fd, buf, sizeof(buf))) {
    error_handling("read ./data.txt error!");
  }
  printf("file data: %s \n", buf);
  return 0;
}