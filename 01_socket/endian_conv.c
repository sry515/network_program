#include <stdio.h>

typedef unsigned short u_short;
typedef unsigned long u_long;

u_short htons(u_short host) {
  char *p = (char *)&host;
  
  char c = *p;
  *p = *(p + 1);
  *(p + 1) = c;

  return host;
}

u_long htonl(u_long host) {
  char *p = (char *)&host;

  char c = *p;
  *p = *(p + 3);
  *(p+3) = c;

  c = *(p+1);
  *(p+1) = *(p+2);
  *(p+2) = c;

  return host;
}

int main(int argc, char **argv) {
  u_short host_port = 0x1234;
  u_short net_port;
  u_long host_addr = 0x12345678;
  u_long net_addr;

  net_port = htons(host_port);
  net_addr = htonl(host_addr);

  printf("host ordered port: %#x \n", host_port); 
  printf("net ordered port: %#x \n", net_port);
  printf("host ordered addr: %#lx \n", host_addr);
  printf("net ordered addr: %#lx \n", net_addr);
}

