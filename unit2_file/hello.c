#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>

int main()
{
	int fd = -1;
	char a[] ="hello world\n";
	fd = open("./data", O_WRONLY|O_CREAT|O_APPEND, 0644);
	//FILE *fd = NULL
	//fd = fopen("./data", "w")
	if (fd<0)
	{
		printf("can note open file \n");
	}
	write(fd ,a,strlen(a));
	while (1);
	close(fd);
	return 0;
}
