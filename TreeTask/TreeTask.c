#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched.h>

#define MAX_DEPT 100
void dfs(struct task_struct *task, int dept)
{

	struct task_struct *child_task;
	struct list_head *list;

	printk(KERN_INFO "Child processes of PID:%d are\n", task->pid);

	list_for_each(list, &task->children)
	{
		child_task = list_entry(list, struct task_struct, sibling);

		char space[MAX_DEPT] = "";
		int i=0;
		for(;i<dept;i++)
			space[i] =" ";

		printk(KERN_INFO "%sProcesses name: %s | id: %d | state: %ld", space, child_task->comm, child_task->pid, child_task->state);
		dfs(child_task, dept+1);

	}
}

int simple_init(void)
{
	printk(KERN_INFO "Loading Module\n");

	dfs(&init_task, 0);

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
MODULE_DESCRIPTION("Tree Tasks");
MODULE_AUTHOR("takkasila");