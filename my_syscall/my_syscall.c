#include <linux_kernel.h>
#include <linux_syscalls.h>
#include <linux/types.h>
#include <linux/sched/signal.h>
#include <linux/sched.h>

SYSCALL_DEFINE1(my_syscall, pid_t, pid)
{
	struct task_struct *task;
	struct sched_info schedinfo;
	task = find_task_by_vpid(pid);
	if(task == NULL){
		return -ESRCH;
	}
	schedinfo = task->sched_info;
	return schedinfo.pcount;
}
