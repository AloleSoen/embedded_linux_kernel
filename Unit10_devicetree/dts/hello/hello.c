#include <linux/module.h> /* Needed by all modules */
#include <linux/kernel.h> /* Needed for KERN_INFO */
#include <linux/time.h>
#include <linux/io.h>
#include <linux/delay.h>
#include <linux/of.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/kdev_t.h>
#include <linux/uaccess.h>
#include <linux/platform_device.h>
#include <linux/slab.h>
#include <linux/mod_devicetable.h>
#include <linux/of_device.h>
#include <linux/platform_device.h>
#include <linux/device.h>
#include <linux/miscdevice.h>

void __iomem *base_addr;

int blink_led_driver_probe(struct platform_device *pdev)
{
    struct device_node	*of_node = NULL;
    uint32_t led_config[2];
    uint32_t reg_array[4];
    uint32_t led_regs[5];
    struct resource *res = NULL;
    // uint64_t start = 0;
    // uint64_t length = 0;
    uint32_t reg_data = 0;
    unsigned int n = 0;

    pr_info("%s, %d\n", __func__, __LINE__);

    of_node=pdev->dev.of_node;

    of_property_read_u32_array(of_node, "reg", reg_array, 2);
    pr_info("reg: %08x %08x\n", reg_array[0], reg_array[1]);

    //Day la cach don gian hon
    res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
    pr_info("read by platform_get_resource: %016x %016x\n", res->start, res->end - res->start);

    of_property_read_u32_array(of_node, "led_config", led_config, 2);
    of_property_read_u32_array(of_node, "led_regs", led_regs, 5);

    base_addr = ioremap(res->start, res->end - res->start);

    //enable output mode for GPIO0_31
    reg_data = readl_relaxed(base_addr + led_regs[3]);
    reg_data &= (~(led_regs[0]));
    writel_relaxed(reg_data, base_addr + led_regs[3]);

    n = led_config[0];
    while (n > 0) {
        writel_relaxed(led_regs[0], base_addr + led_regs[1]);
        msleep(led_config[1] * HZ);
        writel_relaxed(led_regs[0], base_addr + led_regs[2]);
        msleep(led_config[1] * HZ);
        n--;
    }

    return 0;
}

int blink_led_driver_remove(struct platform_device *pdev)
{
    pr_info("Good bye device tree\n");
    return 0;
}

static const struct of_device_id blink_led_of_match[] = {
    {.compatible = "led-example0"},
    {.compatible = "led-example1"},
    {},
};

static struct platform_driver blink_led_driver = {
    .probe = blink_led_driver_probe,
    .remove = blink_led_driver_remove,
    .driver = {
        .name = "blink_led",
        .of_match_table = blink_led_of_match,
    },
};

module_platform_driver(blink_led_driver);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Blink Led kernel module");
