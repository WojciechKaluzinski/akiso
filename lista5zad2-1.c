#include <unistd.h>
#include <signal.h>
#include <stdio.h>

void obslugaSygnalu(int i)
{
 printf("Sygnal zneutralizowany! nr %d\n", i);
}

int main() 
{
 for (int i = 1; i < 65; i++) //mamy 64 sygnały
 {
  if (signal(i, obslugaSygnalu) == SIG_ERR) 
      printf("Nie zlapano sygnalu nr %d\n", i);
 }

 return 0;
} 
