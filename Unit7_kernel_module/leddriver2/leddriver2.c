#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/io.h>
#include <linux/gpio.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Linux Kernel Dev Assistant");
MODULE_DESCRIPTION("A simple Hello World Linux Kernel Module");
MODULE_VERSION("1.0");

#define GPIO_ADDR_BASE 0x44E07000
#define ADDR_SIZE (0x1000)
#define GPIO_SETDATAOUT_OFFSET 0x194
#define GPIO_CLEARDATAOUT_OFFSET 0x190
#define GPIO_OE_OFFSET 0x134
#define LED ~(1 << 31)
#define DATA_OUT (1 << 31)

void __iomem *base_addr;

static int __init hello_init(void)
{
    uint32_t reg_data = 0;

    pr_info("Hello, Kernel World!\n");
    //Lap trinh qua thanh ghi
    base_addr = ioremap(GPIO_ADDR_BASE, ADDR_SIZE);
    reg_data = readl_relaxed(base_addr + GPIO_OE_OFFSET);
    reg_data &= LED;
    writel_relaxed(reg_data, base_addr + GPIO_OE_OFFSET);

    writel_relaxed(DATA_OUT, base_addr + GPIO_SETDATAOUT_OFFSET);
       if (gpio_is_valid(30) == false)
    {
        pr_err("GPIO %d is not valid\n", 30);
        return 0;
    }
    if(gpio_request(30 ,"GPIO_30") < 0) {
        pr_err("ERROR: GPIO %d request\n", 30);
        return 0;
    }
    gpio_direction_output(30, 0);
    gpio_export(30, false);
    gpio_set_value(30, 1);
    
    return 0;
}

static void __exit hello_exit(void)
{
    pr_info("Goodbye, Kernel World!\n");
    writel_relaxed(DATA_OUT, base_addr + GPIO_CLEARDATAOUT_OFFSET);
    gpio_set_value(30, 0);
}

module_init(hello_init);
module_exit(hello_exit);
