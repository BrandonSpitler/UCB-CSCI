#include <linux/kernel.h> //enables use of printk
#include <linux/linkage.h> //protect the stack

//search for arguments on the stack using asmlinkage
asmlinkage long sys_simple_add(int number1, int number2, int* result)
{
	//print message to the kernel syslog
	printk(KERN_ALERT "Number 1: %d \n", number1);
	printk(KERN_ALERT "Number 2: %d \n", number2);

	*result = (number1 + number2);

	printk(KERN_ALERT "Result: %d \n", *result);
	
	return 0;	
}
