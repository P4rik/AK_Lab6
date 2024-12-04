#include <linux/module.h>
#include <linux/printk.h>
#include <linux/bug.h>
#include "hello1.h"

MODULE_LICENSE("Dual BSD/GPL");
MODULE_DESCRIPTION("Hello2 module");
MODULE_AUTHOR("IO-24 Parovenko Danylo");

static int greeting_count = 1;
module_param(greeting_count, int, 0444);
MODULE_PARM_DESC(greeting_count, "Number of times to log the 'Hello, world!' message");

static int __init hello2_startup(void){
    BUG_ON(greeting_count < 0 || greeting_count > 10);
  
    if (greeting_count == 0 || (greeting_count >= 5 && greeting_count <= 10)) {
        pr_warn("Warning: greeting_count is 0 or between 5 and 10. Proceeding.\n");
    }
    
    pr_info("Invoking greetings() from hello1 module\n");
    greetings(greeting_count);

    return 0;
}

static void __exit hello2_shutdown(void)
{
    pr_info("Goodbye from hello2 module\n");
}

module_init(hello2_startup);
module_exit(hello2_shutdown);
