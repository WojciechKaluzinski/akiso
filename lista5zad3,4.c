#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>


int ostatniCharLok(char array[]);
void wyczyscTab(char array[]);
void obslugaRury(char str[]);
void wykonajRure(char ***cmd);


int MAX = 100;
bool amp = false;

int main()
{
 char tabstr[MAX];
 char *s;
 char *tabtest[MAX];
 bool rura_bool;
 int charLok;
 char tabLok[1024];
 char c;
 int dlugoscLinii;
 getcwd(tabLok, 1024);

 while(1)
 {
  rura_bool = false;
  wyczyscTab(tabstr);
  dlugoscLinii = 0;
  printf("%s > ", tabLok);

  while ((c = getchar()) != EOF && c != '\n' && dlugoscLinii < MAX -1)
  {
   if (c == '|')  rura_bool = true;
   tabstr[dlugoscLinii] = c;
   dlugoscLinii++;
  }

  if (dlugoscLinii == 0)
  {
   if (c == EOF)  exit(0);
   continue;
  }

  charLok = ostatniCharLok(tabstr);

  if (tabstr[charLok] == '&')
  {
   amp = true;
   tabstr[charLok] = ' ';
  }

  if (rura_bool)
  {
   obslugaRury(tabstr);
   continue;
  }

  s = strtok(tabstr, " ");
  int i = -1;

  while (s != NULL)
  {
   i++;
   tabtest[i] = s;
   s = strtok(NULL, " ");
  }
  
  i++;
  tabtest[i] = NULL;

  if (strcmp(tabtest[0], "exit") == 0)  exit(0);

  int status;

  if (fork() == 0)
  {
   if (execvp(tabtest[0], tabtest) == -1)
    printf("%s\n", strerror(errno));
   exit(0);
  }
  else
  {
   if (!amp) wait(&status);
  }
 
  amp = false;
  
 }

 return 0;

}



void obslugaRury(char str[])
{
 char **tabrura[MAX];
 char *tabtemp[MAX];
 int i = -1;
 char *s = strtok(str, "|");
 char *s2;

 while (s != NULL)
 {
  i++;
  tabtemp[i] = s;
  s = strtok(NULL, "|");
 }

 for (int x=0; x<=i; x++)
 {
  char **ruraPart;
  ruraPart = malloc(sizeof(char *) * MAX);
  s2 = strtok(tabtemp[x], " ");
  int p = -1;

  while (s2 != NULL)
  {
   p++;
   ruraPart[p] = s2;
   s2 = strtok(NULL, " ");
  }

  p++;
  ruraPart[p] = NULL;
  tabrura[x] = ruraPart;

 }

tabrura[i+1] = NULL;
wykonajRure(tabrura);

for (int x=0; x<=i; x++)
 free(tabrura[x]);

}



int ostatniCharLok(char array[])
{
int i=0;

while (array[i] != '\0')
 i++;
return i-1;

}



void wyczyscTab(char array[])
{
 for (int i=0; i<MAX; i++)
  array[i] = '\0'; 

}



void wykonajRure(char ***cmd)
{
 int tabp[2];
 pid_t pid;
 int fd_in =0;
 int status;

 while (*cmd != NULL)
 {
  pipe(tabp);

  if ((pid = fork()) == -1)  exit(1);

  else if (pid == 0)
  {
   dup2(fd_in, 0);
   if (*(cmd +1) != NULL)  dup2(tabp[1], 1);
 
   close(tabp[0]);
   execvp((*cmd)[0], *cmd);
   exit(0);
  }

  else
  {
   wait(&status);
   close(tabp[1]);
   fd_in = tabp[0];
   cmd++;
  }
 }

}
