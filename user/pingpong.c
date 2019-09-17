#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
	int parent_fd[2];
	int child_fd[2];
	int buff[4];
	int id;

	pipe(parent_fd);
	pipe(child_fd);

	if (fork() == 0)
	{
		// this is child
		id = getpid();
		read(parent_fd[0], buff, 4);
		printf("%d: received %s\n", id, buff);
		write(child_fd[1], "pong", 4);
		exit();
	}
	else
	{
		// this is parent
		id = getpid();
		write(parent_fd[1], "ping", 4);
		read(child_fd[0], buff, 4);
		printf("%d: received %s\n", id, buff);
	}

	exit();
}
