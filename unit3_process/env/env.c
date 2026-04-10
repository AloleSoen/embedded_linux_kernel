#include <stdio.h>
#include <stdlib.h>

extern char **environ;
int main(int argc, char *argv[])
{
    FILE *fp = fopen("/home/leson/leson_linux/unit3_process/env/data", "r");
    int i = 0;
    if (NULL != fp)
        printf("open file data success\n");
    else
        printf("open file data failed\n");
    for (i = 0; environ[i] != NULL; i++) 
    printf("environ[%d]: %s\n", i, environ[i]);
    
   return 0;
} 