#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/gpio.h>

#define GPIO_R 24
#define GPIO_Y 23

#define DEVICE_NAME "mydrv"
#define MYDRV_MAX_LENGTH 4096
#define MIN(a,b) (((a) < (b)) ? (a) : (b))
static int MYDRV_MAJOR;
static char *mydrv_data;
static int mydrv_read_offset, mydrv_write_offset;

static int mydrv_open(struct inode *inode, struct file *file)
{
	if (MAJOR(inode->i_rdev) != MYDRV_MAJOR)
		return -1;
	return 0;
}

static int mydrv_release(struct inode *inode, struct file *file)
{
	if (MAJOR(inode->i_rdev) != MYDRV_MAJOR)
		return -1;
	return 0;
}

static long mydrv_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	printk(KERN_INFO "mydrv_ioctl is invoked \n");
	return 0;
}

static ssize_t mydrv_read(struct file *file, char *buf, size_t count, loff_t *ppos)
{
	if ((buf == NULL) || (count < 0))
		return -EINVAL;
	if ((mydrv_write_offset - mydrv_read_offset) <= 0)
		return 0;
	count = MIN((mydrv_write_offset - mydrv_read_offset), count);
	if (copy_to_user(buf, mydrv_data + mydrv_read_offset, count))
		return -EFAULT;
	mydrv_read_offset =+ count;
	if (mydrv_read_offset == mydrv_write_offset)
	{
		gpio_direction_output(GPIO_R, 1);
		gpio_direction_output(GPIO_Y, 0);
	}
	return count;
}

static ssize_t mydrv_write(struct file *file, const char *buf, size_t count, loff_t *ppos)
{
	if ((buf == NULL) || (count < 0))
		return -EINVAL;
	if (count + mydrv_write_offset >= MYDRV_MAX_LENGTH)
		return 0; /* driver space is too small */
	if (copy_from_user(mydrv_data + mydrv_write_offset, buf, count))
		return -EFAULT;
	mydrv_write_offset += count;
	if (mydrv_read_offset != mydrv_write_offset)
	{
		gpio_direction_output(GPIO_Y, 1);
		gpio_direction_output(GPIO_R, 0);
	}
	return count;
}

struct file_operations mydrv_fops =
{
	.owner = THIS_MODULE,
	.read = mydrv_read,
	.write = mydrv_write,
	.compat_ioctl = mydrv_ioctl,
	.open = mydrv_open,
	.release = mydrv_release,
};

int mydrv_init(void)
{
	if (register_chrdev(MYDRV_MAJOR = 243, DEVICE_NAME, &mydrv_fops) < 0)
	{
		printk(KERN_INFO "can't be registered \n");
		return MYDRV_MAJOR;
	}
	if ((mydrv_data = (char *)kmalloc(MYDRV_MAX_LENGTH * sizeof(char), GFP_KERNEL)) == NULL)
	{
		unregister_chrdev(MYDRV_MAJOR, DEVICE_NAME);
		return -ENOMEM;
	}
	mydrv_read_offset = mydrv_write_offset = 0;
	gpio_direction_output(GPIO_R, 1);
	return 0;
}

void mydrv_cleanup(void)
{
	gpio_direction_output(GPIO_R, 0);
	gpio_direction_output(GPIO_Y, 0);
	kfree(mydrv_data);
	unregister_chrdev(MYDRV_MAJOR, DEVICE_NAME);
}

module_init(mydrv_init);
module_exit(mydrv_cleanup);

MODULE_LICENSE("GPL");
