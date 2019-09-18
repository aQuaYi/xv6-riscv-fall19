#include "kernel/types.h"
#include "user/user.h"

void redirect(int k, int pd[])
{
	close(k);
	dup(pd[k]);
	close(pd[0]);
	close(pd[1]);
}

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

int sieve()
{
	int p;
	if (read(0, &p, sizeof(p)) == 0)
	{
		exit();
	}

	int pid = getpid();
	printf("%d prime %d\n", pid, p);

	int pd[2];
	pipe(pd);

	if (fork())
	{
		redirect(0, pd);
		sieve();
	}
	else
	{
		redirect(1, pd);
		cull(p);
	}
	exit();
}

int main(int argc, char *argv[])
{
	int pd[2];
	pipe(pd);

	if (fork())
	{
		redirect(0, pd);
		sieve();
	}
	else
	{
		redirect(1, pd);
		source();
	}
	exit();
}
