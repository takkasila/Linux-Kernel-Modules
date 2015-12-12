#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched.h>


int simple_init(void)
{
	printk(KERN_INFO "Loading Module\n");

	struct task_struct *task;

	for_each_process(task)
	{
		printk(KERN_INFO "Processs name: %s | id: %d | state: %ld"
			, task->comm, task->pid, task->state);
	}

	printk(KERN_INFO "Loaded Module\n");
	return 0;
}

void simple_exit(void)
{

	printk(KERN_INFO "Removed Module\n");
}

module_init(simple_init);
module_exit(simple_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Listing Tasks");
MODULE_AUTHOR("takkasila");