/*kernel version   */
#include <linux/kernel.h>       /* We're doing kernel work */
#include <linux/module.h>       /* Specifically, a module */
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/time.h>
#include<linux/init.h>
#include <linux/cdev.h>
#include<linux/types.h>
#include <linux/kdev_t.h>
#include <linux/device.h>
#include <linux/random.h>
#include "chardev.h"
#define SUCCESS 0
#define DEVICE_NAME "imu_char"

static dev_t first;        // variable for device number
static struct cdev c_dev;  // variable for the character device structure
static struct class *cls;  // variable for the device class


/*
 * Is the device open right now? Used to prevent
 * concurent access into the same device
 */
static int Device_Open = 0;

 static int devc;  //numbering the 10 devices from 1 to 10
 static char axis;

 uint16_t i2c_val,i ;

 
 //file open //
static int i2c_open(struct inode *inode, struct file *file)
{
//#ifdef DEBUG
        printk(KERN_INFO "device_open(%p)\n", file);
//#endif


    /*To avoid intantiating two process simultaneously*/
    if (Device_Open)
        return -EBUSY;

    Device_Open++;
    try_module_get(THIS_MODULE);
    return SUCCESS;
}

static int i2c_close(struct inode *inode, struct file *file)
{
//#ifdef DEBUG
    printk(KERN_INFO "device_release(%p,%p)\n", inode, file);
//#endif

   
    Device_Open--;

    module_put(THIS_MODULE);
    return SUCCESS;
}

/*
 * This function is called whenever a process which has already opened the
 * device file attempts to read from it.
 */
static ssize_t i2c_read(struct file *file,   /* see include/linux/fs.h   */
                           char __user * buffer,        /* buffer to be
                                                         * filled with data */
                           size_t length,       /* length of the buffer     */
                           loff_t * offset)
{
   
    int bytes_read = 0;
    int ret_val;	

    get_random_bytes(&i,sizeof(i));

        if(axis =='X')
         { 
           i2c_val= 64*(i%1024);
           printk("10 bit Value : %d ",i2c_val);
         }

        ret_val= copy_to_user(buffer, &i2c_val , sizeof(i2c_val));

	return ret_val;

 

    return bytes_read;
}



/*
 * This function is called whenever a process tries to do an ioctl on our
 * device file.
 */
long i2c_ioctl(struct file *file,             /* ditto */
                  unsigned int ioctl_num,        /* number and param for ioctl */
                  unsigned long ioctl_param)
{
    int *temp_devc;

    /*
     * Switch according to the ioctl called
     */
    switch (ioctl_num) {
    case IOCTL_GET_GYROSCOPEX:
         temp_devc = (int *)ioctl_param;
         get_user(devc,temp_devc);
         printk(KERN_INFO "Device - %d is selected\n",devc);
         

         break;

    case IOCTL_GET_GYROSCOPEY:
         temp_devc = (int *)ioctl_param;
         get_user(devc,temp_devc);
         printk(KERN_INFO "Device - %d is selected\n",devc);
         

         break;

    case IOCTL_GET_GYROSCOPEZ:
         temp_devc = (int *)ioctl_param;
         get_user(devc,temp_devc);
         printk(KERN_INFO "Device - %d is selected\n",devc);
         

         break;

   case IOCTL_GET_ACCELEROMETERX:
         temp_devc = (int *)ioctl_param;
         get_user(devc,temp_devc);
         printk(KERN_INFO "Device - %d is selected\n",devc);
         

         break;

    case IOCTL_GET_ACCELEROMETERY:
         temp_devc = (int *)ioctl_param;
         get_user(devc,temp_devc);
         printk(KERN_INFO "Device - %d is selected\n",devc);
         

         break;

    case IOCTL_GET_ACCELEROMETERZ:
         temp_devc = (int *)ioctl_param;
         get_user(devc,temp_devc);
         printk(KERN_INFO "Device - %d is selected\n",devc);
         

         break;

    case IOCTL_GET_COMPASSX:
         temp_devc = (int *)ioctl_param;
         get_user(devc,temp_devc);
         printk(KERN_INFO "Device - %d is selected\n",devc);
         

         break;

    case IOCTL_GET_COMPASSY:
         temp_devc = (int *)ioctl_param;
         get_user(devc,temp_devc);
         printk(KERN_INFO "Device - %d is selected\n",devc);
         

         break;

    case IOCTL_GET_COMPASSZ:
         temp_devc = (int *)ioctl_param;
         get_user(devc,temp_devc);
         printk(KERN_INFO "Device - %d is selected\n",devc);
         

         break;

    case IOCTL_GET_BAROMETER:
         temp_devc = (int *)ioctl_param;
         get_user(devc,temp_devc);
         printk(KERN_INFO "Device - %d is selected\n",devc);
         

         break;

        }

    return SUCCESS;
}

/* Module Declarations */

/*
 *flie operations mapping to system calls
 */
struct file_operations fops = {
        .read = i2c_read,
        .unlocked_ioctl = i2c_ioctl,
        .open = i2c_open,
        .release = i2c_close,      /* close */
};

/*
 * Initialize the module - Register the character device
 */
int myi2c_init(void)
{
   // reserve <major, minor>
	if (alloc_chrdev_region(&first, 0, 1, "imu_char") < 0)
	{
		return -1;
	}
	
	// dynamically create device node in /dev directory
    if ((cls = class_create(THIS_MODULE, "charadc")) == NULL)
	{
		unregister_chrdev_region(first, 1);
		return -1;
	}
    if (device_create(cls, NULL, first, NULL, DEVICE_NAME ) == NULL)
	{
		class_destroy(cls);
		unregister_chrdev_region(first, 1);
		return -1;
	}
	
	// Link fops and cdev to device node
    cdev_init(&c_dev, &fops);
    if (cdev_add(&c_dev, first, 1) == -1)
	{
		device_destroy(cls, first);
		class_destroy(cls);
		unregister_chrdev_region(first, 1);
		return -1;
	}
      
    	printk(KERN_INFO "I2C registered successfully\n");

   
    return 0;
}

/*
 * Cleanup - unregister the appropriate file from /proc
 */
void myi2c_exit(void)
{

        cdev_del(&c_dev);
	device_destroy(cls, first);
	class_destroy(cls);
	unregister_chrdev_region(first, 1);
	printk(KERN_INFO "I2C driver unregistered\n\n");


}


module_init(myi2c_init);
module_exit(myi2c_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Swati Purna Sahoo");
MODULE_DESCRIPTION("I2C Driver");
