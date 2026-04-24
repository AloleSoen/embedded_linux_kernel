#include <linux/module.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/i2c.h>
#include <linux/delay.h>
#include <linux/kernel.h>

static int i2coled_probe_new(struct i2c_client *client)
{
    pr_info("%s , %d  \n", __func__ , __LINE__);
    pr_info("device address: %02x\n", client -> addr);
    return 0;
};

static int i2coled_remove(struct i2c_client *client)
{
    pr_info("%s , %d  \n", __func__ , __LINE__);
    return 0;
};

static struct of_device_id i2coled_of_id[] = {
    { .compatible = "ssd1306", },
    { }
};


static struct i2c_driver i2coled = {
    .probe_new = i2coled_probe_new,
    .remove = i2coled_remove,
    .driver = {
        .name = "i2coled",
        .of_match_table = i2coled_of_id
    },
};

module_i2c_driver(i2coled);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("AloLeSon");
MODULE_DESCRIPTION("i2c kernel module for ssd1306 oled");