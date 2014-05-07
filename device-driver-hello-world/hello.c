/* A hello world USB device driver.
 *
 * Registers a simple USB device driver that prints "Hello World!" when an
 * iPhone is connected to the computer via a USB cord. Like all kernel
 * modules, we load `linux/module.h`. We use `linux/kernel.h` to get the
 * macros we use in `printk`. We use `linux/init.h` to register the
 * initialization and cleanup functions.
 *
 * (c) 2014 Alex Clemmer <clemmer.alexander@gmail.com>
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/usb.h>

/* Module meteadata */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Alex Clemmer");
MODULE_DESCRIPTION("A Hello World device driver.");

/* Prototypes for the functions that will run when we connect and
 * disconnect a USB iPhone.
 */
static int hw_probe(struct usb_interface *interface, const struct usb_device_id *id);
static void hw_disconnect(struct usb_interface *interface);

/* Identifies the USB-connected iPhone. Vendor ID is assigned by the USB
 * forum, while product ID is assigned by the vendor.
 */
#define IPHONE_VENDOR_ID 0x05ac
#define IPHONE_PRODUCT_ID 0x12a0

/* Struct we will use to identify vanilla USB-connected iPhone */
static struct usb_device_id hw_iphone_id [] = {
	{ USB_DEVICE(IPHONE_VENDOR_ID, IPHONE_PRODUCT_ID) },
	{ }
};

/* Simple device driver for a USB-connected iPhone */
static struct usb_driver hw_usb_driver = {
	.name       = "hw_usb_driver",
	.probe      = hw_probe,
	.disconnect = hw_disconnect,
	.id_table   = hw_iphone_id,
};

/* exports iPhone id struct to userspace */
MODULE_DEVICE_TABLE (usb, hw_iphone_id);

/* Function runs to determine if we will manage the hotplugged device */
static int hw_probe(struct usb_interface *interface, const struct usb_device_id *id)
{
	printk(KERN_DEBUG "hwusb: probe module\n");
	return 0;
}

/* Function runs when we disconnect the device or the driver module is
 * unloaded
 */
static void hw_disconnect(struct usb_interface *interface)
{
	printk(KERN_DEBUG "hwusb: disconnected\n");
}

/* Initialization method -- runs when it's loaded by the kernel. */
static int __init hello_world_init(void)
{
	int result;

	result = usb_register(&hw_usb_driver);
	if (result) {
		printk(KERN_DEBUG "hwusb: registration failed\n");
	}
	else {
		printk(KERN_DEBUG "hwusb: registration successful\n");
	}

	return result;
}

/* Cleanup method -- runs when the kernel takes it down. */
static void __exit hello_world_cleanup(void)
{
	usb_deregister(&hw_usb_driver);
	printk(KERN_DEBUG "hwusb: exited\n");
}

/* Register the initialization and cleanup functions. */
module_init(hello_world_init);
module_exit(hello_world_cleanup);



