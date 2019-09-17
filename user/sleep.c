#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		fprintf(2, "USAGE: sleep seconds\n", 20);
		exit();
	}

	int sec;
	sec = atoi(argv[1]);
	if (sec > 0)
	{
		sleep(sec);
	}
	else
	{
		fprintf(2, "Invalid interval: %s\n", argv[1]);
	}

	exit();
}
