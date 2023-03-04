#include <netinet/in.h>
#include <stdio.h>
#include <arpa/inet.h>

int main(int argc, char **argv) {
  char *addr_1 = "1.2.3.4";
  char *addr_2 = "1.2.3.256";

  unsigned long conv_addr = inet_addr(addr_1);
  if (INADDR_NONE == conv_addr) {
    printf("Error occured! \n");
  } else {
    printf("Network ordered interger addr: %#lx \n", conv_addr);
  }

  conv_addr = inet_addr(addr_2);
  if (INADDR_NONE == conv_addr) {
    printf("Error occured! \n");
  } else {
    printf("Network ordered interger addr: %#lx \n", conv_addr);
  } 

  return 0;
}