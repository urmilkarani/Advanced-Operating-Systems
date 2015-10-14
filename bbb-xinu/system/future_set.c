#include <future.h>
syscall future_set(future *f, int *value)
{
	//register struct procent *prptr;
	//prptr = &proctab[currpid];
	
	if(f->state == FUTURE_VALID || f->state == FUTURE_EMPTY)		
	{
		return SYSERR;
	}
	else
	{
		
		//prptr->prstate = PR_READY;
		//insert(currpid, readylist, prptr->prprio);
		
		f->value = value;
		f->state = FUTURE_VALID;
		//resched();

		
		ready(f->pid);
		return OK;
	}
}
