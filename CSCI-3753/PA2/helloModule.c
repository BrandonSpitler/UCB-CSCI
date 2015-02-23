#include<linux/init.h> //required for initialization of the module
#include<linux/module.h> //required to the kernel know this is a Loadable Kernel Module

int hello_init(void)
{
	printk(KERN_ALERT "inside %s function\n",__FUNCTION__);
	return 0;
}

int hello_exit(void)
{
	printk(KERN_ALERT "inside %s function\n",__FUNCTION__);
	return 0;
}

module_init(hello_init);
module_exit(hello_exit);
