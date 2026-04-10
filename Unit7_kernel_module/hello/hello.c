#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Linux Kernel Dev Assistant");
MODULE_DESCRIPTION("A simple Hello World Linux Kernel Module");
MODULE_VERSION("1.0");


static int __init hello_init(void)
{

    pr_info("Hello, Kernel World!\n");
    return 0;
}

static void __exit hello_exit(void)
{
    pr_info("Goodbye, Kernel World!\n");
}

module_init(hello_init);
module_exit(hello_exit);
