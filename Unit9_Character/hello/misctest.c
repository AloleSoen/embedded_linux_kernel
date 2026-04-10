#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>

struct config
{
    int times;
};

#define MAGIC_NO 100
#define SEND_DATA_CMD _IOW(MAGIC_NO, sizeof(struct config), struct config *)
#define GET_DATA_CMD _IOR(MAGIC_NO, sizeof(struct config), struct config *)

int main()
{
    int fd = 0;
    char data[8];
    int len = 0;
    struct config config_data = { .times = 10 };
    struct config get_data;

    fd = open("/dev/misc_example", O_RDWR);
    if (fd > 0)
    {
        len = ioctl(fd, SEND_DATA_CMD, &config_data);
        len = ioctl(fd, GET_DATA_CMD, &get_data);
        len = write(fd, "1", strlen("1"));
        len = write(fd, "0", strlen("0"));
        len = write(fd, "1", strlen("1"));
        memset(data, 0, sizeof(data));
        len = read(fd, data, 1);
        close(fd);
    }
    return 0;
}