#include "kernel/types.h"
#include "user/user.h"

void source()
{
	int i;
	for (i = 2; i < 36; i++)
	{
		// write 前会重定向
		write(1, &i, sizeof(i));
	}
}

void cull(int p)
{
	int n;
	// read 前会重定向
	while (read(0, &n, sizeof(n)))
	{
		if (n % p != 0)
		{
			// write 前会重定向
			write(1, &n, sizeof(n));
		}
	}
}

void redirect(int k, int pd[])
{
	close(k);
	dup(pd[k]);
	close(pd[0]);
	close(pd[1]);
}

void sink()
{
	int pid = getpid();
	printf("sink is %d\n", pid);

	int pd[2];
	int p;

	// read 前会重定向
	while (read(0, &p, sizeof(p)))
	{
		int pid = getpid();
		printf("%d prime %d\n", pid, p);
		pipe(pd);
		if (fork())
		{
			// this is parent
			redirect(0, pd);
			continue;
		}
		else
		{
			// this is child
			redirect(1, pd);
			cull(p);
		}
	}
}

int main(int argc, char *argv[])
{
	int pid = getpid();
	printf("main is %d\n", pid);

	int pd[2];
	pipe(pd);

	if (fork())
	{
		// this is parent
		redirect(0, pd);
		sink();
	}
	else
	{
		// this is child
		redirect(1, pd);
		source();
	}

	// pid = getpid();
	// printf("%d done\n", pid);
	exit();
}
