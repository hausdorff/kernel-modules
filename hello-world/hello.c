/* A simple Hello World kernel module.
 *
 * Prints "Hello World!" when the module is loaded by the kernel. Like all
 * modules, we load `linux/module.h`. We use `linux/kernel.h` to get the
 * macros we use in `printk`. We use `linux/init.h` to register the
 * initialization and cleanup functions.
 *
 * (c) 2014 Alex Clemmer <clemmer.alexander@gmail.com>
 */

#include <linux/module.h> 
#include <linux/kernel.h>
#include <linux/init.h>

/* Module meteadata */
MODULE_LICENSE("MIT");
MODULE_AUTHOR("Alex Clemmer");
MODULE_DESCRIPTION("A simple Hello World kernel module.");

/* Initialization method -- runs when it's loaded by the kernel. */
static int __init hello_world_init(void)
{
  printk(KERN_DEBUG "Hello World!\n");
  return 0;
}

/* Cleanup method -- runs when the kernel takes it down. */
static void __exit hello_world_cleanup(void)
{
  // nop
}

/* Register the initialization and cleanup functions. */
module_init(hello_world_init);
module_exit(hello_world_cleanup);
