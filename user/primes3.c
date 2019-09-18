#include "kernel/types.h"
#include "user/user.h"

void source(int to)
{
	int i;
	for (i = 2; i < 36; i++)
	{
		write(to, &i, sizeof(i));
	}
}

void cull(int p, int form, int to)
{
	int n;
	while (read(form, &n, sizeof(n)))
	{
		if (n % p != 0)
		{
			write(to, &n, sizeof(n));
		}
	}
}

int sieve(int from)
{
	int p;
	if (read(from, &p, sizeof(p)) == 0)
	{
		exit();
	}

	int pid = getpid();
	printf("%d prime %d\n", pid, p);

	int pd[2];
	pipe(pd);

	if (fork())
	{
		sieve(pd[0]);
	}
	else
	{
		cull(p, from, pd[1]);
	}
	exit();
}

int main(int argc, char *argv[])
{
	int pd[2];
	pipe(pd);

	if (fork())
	{
		sieve(pd[0]);
	}
	else
	{
		source(pd[1]);
	}
	exit();
}