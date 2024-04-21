#include <cerrno>
#include <cstdio>
#include <stdio.h>
#include <unistd.h>


int startChild(char* pathChild, unsigned indexChild, char* pathEnv);

int createChild(char* pathChild, unsigned indexChild, char* pathChildEnv)
{
	printf("createChild ST\n");
	pid_t pid;

	pid = fork();
	if (pid == -1)
	{
		printf("Error in fork(): %d\n", errno);
		return -1;
	}
	if (pid == 0)
	{
		startChild(pathChild, indexChild, pathChildEnv);
		return -1;
	}
	printf("createChild OK\n");

	return 0;
}

int startChild(char* path, unsigned index, char* pathEnv)
{
	printf("startChild ST\n");
	char* argv[] = { NULL, NULL, NULL };
	char nameProgram[9] = { 0, };

	sprintf(nameProgram, "child_%02d", index);
	argv[0] = nameProgram;
	argv[1] = pathEnv;

	printf("Before exec child process \n");
	execve(path, argv, NULL);

	// we get here only in case of Error

	printf("Error in execve(): %d\n", errno);
	printf("startChild OK\n");

	return 0;
}
