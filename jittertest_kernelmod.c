#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/timer.h>

MODULE_LICENSE("GPL");

static struct timer_list my_timer;

void my_timer_callback( unsigned long data )
{
    /* do your timer stuff here */
}

int init_module(void)
{
    /* setup your timer to call my_timer_callback */
    setup_timer(&my_timer, my_timer_callback, 0);

    /* set timer frequency */
    mod_timer(&my_timer, jiffies + usecs_to_jiffies(500));
    return 0;
}

void cleanup_module(void)
{
    /* remove kernel timer when unloading module */
    del_timer(&my_timer);
    return;
}
