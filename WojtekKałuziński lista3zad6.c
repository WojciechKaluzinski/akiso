#include <stdio.h>

int main(int argc, char *argv[])
{

for (int i=0; i<256; i++)
{
 for (int j=0; j<256; j++)
 {
  for (int k=0; k<256; k++)
   {
     printf("\x1b[38;2;%d;%d;%dmHello World!\n",i,j,k);
   } 

 }
}

return 0;
}
