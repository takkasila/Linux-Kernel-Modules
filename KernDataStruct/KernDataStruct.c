#include <linux/types.h>
#include <linux/list.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>

typedef struct birthday
{
	int day;
	int month;
	int year;
	struct list_head list;
	
}birthday;

static LIST_HEAD(birthday_list);

int simple_init(void)
{
	printk(KERN_INFO "Loading Module\n");


	int i=0;
	for(i=0 ; i<5 ; i++)
	{
		birthday *person;
		person = kmalloc(sizeof(*person), GFP_KERNEL);
		person->day = i;
		person->month = (i+2)%12;
		person->year = 1995 + i;

		INIT_LIST_HEAD(&person->list);
		list_add_tail(&person->list, &birthday_list);
	}


	birthday *bth_ptr;

	list_for_each_entry(bth_ptr, &birthday_list, list)
	{
		printk(KERN_INFO "%d/%d/%d\n",bth_ptr->year, bth_ptr->day, bth_ptr->month);
	}

	printk(KERN_INFO "Loaded Module\n");
	return 0;
}

void simple_exit(void)
{
	printk(KERN_INFO "Removing Module\n");

	birthday *bth_ptr, *next;

	list_for_each_entry_safe(bth_ptr, next, &birthday_list, list)
	{
		list_del(&bth_ptr->list);
		kfree(bth_ptr);
	}

	printk(KERN_INFO "Removed Module\n");
}

module_init(simple_init);
module_exit(simple_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Kernal Data Structure");
MODULE_AUTHOR("takkasila");