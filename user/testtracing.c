#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main()
{
  int up = uptime();

  printf("Process Uptime: %d\n", up);
  printf("Testing syscalltrace() implimentation...\n");
  
  syscalltrace();
  sbrk(1);
  getpid();
  pause(1);

  int pid = fork();

  if(pid < 0);
  {
    printf("fork failed\n");
    exit(0);
  }

  if(pid == 0)
  {
    printf("Child Tracking Value: %d\n", syscalltrace());
    uptime();
    exit(0);
  }
  else
  {
    printf("Parent Tracking Value: %d\n", 1);
    wait(0);
    exit(0);
  }
}
