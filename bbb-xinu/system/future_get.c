#include <future.h>
syscall future_get(future *f, int *value)
{
	intmask	mask;	
	struct	procent *prptr;
	prptr = &proctab[currpid];
	mask = disable();	
	if(f->state == FUTURE_EMPTY)		
	{		
		f->pid = currpid;
		f->state = FUTURE_WAITING;
		while(f->state != FUTURE_VALID)
			resched();
		*value = f->value;
		restore(mask);		
		return OK;
	}
	else if(f->state == FUTURE_WAITING )
	{		
		restore(mask);				
		return SYSERR;
	}
	else
	{	
		*value = f->value;
		f->pid = NULL;
		f->state = FUTURE_EMPTY;
		restore(mask);		
		return OK;
	}
}

