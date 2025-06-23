#include <linux/kernel.h>
#include<linux/syscalls.h>

SYSCALL_DEFINE0(helloworld) {
	printk("Hello, Janginhwan!\n");
	printk("214683");
	return 0;
}
