/* clkhandler.c - clkhandler */

#include <xinu.h>

int deleteArp(void);
struct arpentry arpcache[ARP_SIZ];

/*-----------------------------------------------------------------------
 * clkhandler - high level clock interrupt handler
 *-----------------------------------------------------------------------
 */
void	clkhandler()
{

	static uint32 count1000 = 1000;	/* variable to count 1000ms */
	volatile struct am335x_timer1ms *csrptr = 0x44E31000;
					/* Pointer to timer CSR	    */

	/* If there is no interrupt, return */

	if((csrptr->tisr & AM335X_TIMER1MS_TISR_OVF_IT_FLAG) == 0) {
		return;
	}

	/* Acknowledge the interrupt */

	csrptr->tisr = AM335X_TIMER1MS_TISR_OVF_IT_FLAG;

	/* Decrement 1000ms counter */

	count1000--;

	/* After 1 sec, increment clktime */

	if(count1000 == 0) {
		clktime++;
		deleteArp();
		count1000 = 1000;
	}

	/* check if sleep queue is empty */

	if(!isempty(sleepq)) {

		/* sleepq nonempty, decrement the key of */
		/* topmost process on sleepq		 */

		if((--queuetab[firstid(sleepq)].qkey) == 0) {

			wakeup();
		}
	}

	/* Decrement the preemption counter */
	/* Reschedule if necessary	    */

	if((--preempt) == 0) {
		preempt = QUANTUM;
		resched();
	}
}
int deleteArp(void)
	{
		int32 i;
		for(i = 0; i<ARP_SIZ; i++)
		{
			if(arpcache[i].arstate != AR_FREE)
			{
				if((clktime - arpcache[i].time) >= ARP_TIMESUP)
				{
					arpcache[i].arstate = AR_FREE;
				}
			}
		}
	return 1;
	}
