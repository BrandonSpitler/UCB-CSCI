#include<linux/init.h>
#include<linux/module.h>

#include<linux/fs.h> //get functions related to device driver
#include<asm/uaccess.h> //get data from userspace to kernel and visa versa
#define BUFFER_SIZE 1024

static char device_buffer[BUFFER_SIZE];
int openCounter = 0;
int closeCounter = 0;

ssize_t simple_char_driver_read (struct file *pfile, char __user *buffer, size_t length, loff_t *offset)
{
  /* *buffer is the userspace buffer to where you are writing the data you want to be read from the device file*/
  /*  length is the length of the userspace buffer*/
  /*  current position of the opened file*/
  /* copy_to_user function. source is device_buffer (the buffer defined at the start of the code) and destination is the userspace buffer *buffer */
  int size = strlen(device_buffer); //keeps track of the number of items in the buffer
  int readbytes; //keeps track of the bytes we are reading

  if (length > BUFFER_SIZE - *offset)
    length = BUFFER_SIZE - *offset; //if the desired length is longer than we can read, decrease it

  if(size > length)
    size = length; //if the number of items in the buffer is greater than the length, decrease it
  
  if (length == 0)
    return 0; //exit for EOF
 
  //copy_to_user returns the number of bytes left to copy
  readbytes = length - copy_to_user(buffer, device_buffer + *offset, length);
  printk(KERN_ALERT "The device has read %d bytes.\n", size);

  //increment the offset by the number of bytes read
  *offset += readbytes;

  return readbytes;
}


ssize_t simple_char_driver_write (struct file *pfile, const char __user *buffer, size_t length, loff_t *offset)
{
  /* *buffer is the userspace buffer where you are writing the data you want to be written in the device file*/
  /*  length is the length of the userspace buffer*/
  /*  current position of the opened file*/
  /* copy_from_user function. destination is device_buffer (the buffer defined at the start of the code) and source is the userspace buffer *buffer */ 
  int size = strlen(device_buffer); //keep track of the number of items in the buffer
  int writebytes;

  if (length > BUFFER_SIZE - *offset)
    length = BUFFER_SIZE - *offset; //if the desired length is longer than we can read, decrease it

  if (length == 0)
    return 0; //exit for EOF
 
  writebytes = length - copy_from_user(device_buffer + size, buffer, length);

  printk(KERN_ALERT "The device has written %d bytes.\n", writebytes);
 
  *offset += writebytes;

  return writebytes;
}


int simple_char_driver_open (struct inode *pinode, struct file *pfile)
{
  /* print to the log file that the device is opened and also print the number of times this device has been opened until now*/
  printk(KERN_ALERT "The device is opened.\n");
  printk(KERN_ALERT "The device has been opened %d times.\n", ++openCounter);
  return 0;
}


int simple_char_driver_close (struct inode *pinode, struct file *pfile)
{
  /* print to the log file that the device is closed and also print the number of times this device has been closed until now*/
  printk(KERN_ALERT "The device is closed.\n");
  printk(KERN_ALERT "The device has been closed %d times.\n", ++closeCounter);
  return 0;
}

struct file_operations simple_fops = {

  .owner   = THIS_MODULE,
  /* add the function pointers to point to the corresponding file operations. look at the file fs.h in the linux souce code*/
  .write = simple_char_driver_write,
  .read = simple_char_driver_read,
  .open = simple_char_driver_open,
  .release = simple_char_driver_close,
};

static int simple_char_driver_init(void)
{
  /* print to the log file that the init function is called.*/
  /* register the device */
  printk(KERN_ALERT "The %s function is called.\n",__FUNCTION__);
  register_chrdev(240, "simple_character_device", &simple_fops);
  return 0;
}

static int simple_char_driver_exit(void)
{
  /* print to the log file that the exit function is called.*/
  /* unregister  the device using the register_chrdev() function. */
  printk(KERN_ALERT "The %s function is called.\n",__FUNCTION__);
  unregister_chrdev(240, "simple_character_device");
  return 0;
}

module_init(simple_char_driver_init); //executes when the module is installed
module_exit(simple_char_driver_exit); //executes when the module is uninstalled
