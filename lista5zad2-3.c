#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <sys/wait.h>

int count = 1;

void obslugaSygnalu(int nr) {
 printf("%d Sygnal odebrany\n",count);
 count++;
}

int main() 
{
  pid_t pid;
  pid = fork();
 
  if (pid == 0) 
  {
    for (int i = 0; i < 10; i++) 
    {
      printf("Wysyłany %d sygnał\n",i+1);
      kill(getppid(), SIGUSR1);
    }
  } 
  else
  {
   signal(SIGUSR1, obslugaSygnalu);
   while(1);
  } 
 
 return 0;
} 
