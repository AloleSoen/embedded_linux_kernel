#include<stdio.h>
#include <stdlib.h>
void term()
{
    exit(1);
}

int main(int argc, char *argv[])
{
    int i = 0 ;
    char *b = NULL;
    *b = 'A';
    //term();
    for ( i = 0; i < argc; i++)
    {
        printf("argv[%d]: %s\n",i,argv[i]);
    } 
   return 0;
}    