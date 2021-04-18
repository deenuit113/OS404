#include "types.h"
#include "stat.h"
#include "user.h"

#define PRIO_BASE 20
#define INNER_LOOP 1000
#define OUTER_LOOP 20
#define PI 3.14

int main(int argc, char **argv)
{
	int pid = getpid();
	float dummy = 0;
	int i, j;
	printf(1, "=== TEST START ===\n");
	setnice(pid, PRIO_BASE);

	pid = fork();
	if(pid == 0)
	{
		for(i=0; i<OUTER_LOOP/2; i++)
		{
			for(j=0; j<INNER_LOOP; j++)
				dummy += PI*j;
			printf(1, "IN (HI), i = %d, dummy = %x\n", i, dummy);
		}
		
		pid = fork();
		if(pid == 0)
		{
			for(i=0; i<OUTER_LOOP; i++)
			{
				for(j=0; j<INNER_LOOP; j++)
					dummy += PI*j;
				printf(1, "In (MID), i = %d, dummy = %x\n",i,dummy);
			}
		}
		else
		{
			for(i=0; i<OUTER_LOOP/2; i++)
			{
				for(j=0; j<INNER_LOOP/2;j++)
					dummy += PI*j;
				printf(1, "In (HI), i = %d, dummy = %x\n", i, dummy);
			}
			wait();
		}
	}
	else
	{
		for(i=0; i<OUTER_LOOP;i++)
		{
			for(j=0; j<INNER_LOOP;j++)
				dummy += PI*j;
			printf(1, "In (LO), i = %d, dummy = %x\n", i, dummy);
		}
		wait();
		printf(1, "=== TEST DONE === \n");

	}
	exit();

}
