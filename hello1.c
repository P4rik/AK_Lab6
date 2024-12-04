#include <linux/module.h>
#include <linux/printk.h>
#include <linux/ktime.h>
#include <linux/slab.h>
#include <linux/list.h>
#include "hello1.h"

MODULE_LICENSE("Dual BSD/GPL");
MODULE_DESCRIPTION("Hello1 module");
MODULE_AUTHOR("IO-24 Parovenko Danylo");

static LIST_HEAD(greeting_list);
static int kmalloc_counter_fails = 0;

void greetings(int repetitions)
{
    struct greeting_data *data;
    int index;

    for (index = 0; index < repetitions; index++) {
	kmalloc_counter_fails++;
	if (kmalloc_counter_fails == 5){
	pr_err("Simulated kmalloc failure during the 5th iteration");
	return;
	}

        data = kmalloc(sizeof(*data), GFP_KERNEL);
        if (!data) {
            pr_err("Memory allocation failed\n");
            return;
        }

        data->time_start = ktime_get();
        pr_info("Hello, world!\n");
        data->time_end = ktime_get();
        list_add_tail(&data->list, &greeting_list);
    }
}

EXPORT_SYMBOL(greetings);

static void __exit hello1_cleanup(void)
{
    struct greeting_data *data, *tmp;

    list_for_each_entry_safe(data, tmp, &greeting_list, list) {
        pr_info("Greeting duration: %lld ns\n",
                ktime_to_ns(data->time_end) - ktime_to_ns(data->time_start));
        list_del(&data->list);
        kfree(data);
    }
}

module_exit(hello1_cleanup);
