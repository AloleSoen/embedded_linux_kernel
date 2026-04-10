#include <stdio.h>
#include <unistd.h>

int main()
{
    int p = 0 ;
    p = fork();

    if(0 == p)
    { 
        printf("I am child process\n");
        execl("/home/leson/leson_linux/unit3_process/fork/new_program","l", (char *)NULL);
    }
    else
    {
        printf("I am parent process\n");
    }
    return 0;
} 