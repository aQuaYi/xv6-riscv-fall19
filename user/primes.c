#include "kernel/types.h"
#include "user/user.h"

int sieve(int fd)
{
	int id = getpid();
	printf("into %d\n", id);

	int p;
	if (read(fd, &p, sizeof(p)) == 0)
	{
		exit();
	}
	printf("prime %d\n", p);

	int next[2];
	pipe(next);

	if (fork() == 0)
	{
		sieve(next[0]);
	}
	else
	{
		int n;
		while (read(fd, &n, sizeof(n)) != 0)
		{
			if (n % p != 0)
			{
				write(next[1], &n, sizeof(n));
			}
		}
	}
	exit();
}

int main(int argc, char *argv[])
{
	int p[2];
	pipe(p);

	if (fork() == 0)
	{
		sieve(p[0]);
	}
	else
	{
		for (int i = 2; i < 36; i++)
		{
			write(p[1], &i, sizeof(i));
			printf("w: %d\n", i);
		}
	}
	exit();
}
