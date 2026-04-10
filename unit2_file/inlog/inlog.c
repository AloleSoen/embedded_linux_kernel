#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include <fcntl.h>

FILE *fd = NULL;
void write_log(char *log)
	{
		fd = fopen("./data", "w");
		fwrite(log ,1, strlen(log), fd);
        fclose(fd);
	}
int main()
{
  
    write_log("log can ghi"); 

	return 0;
}
 