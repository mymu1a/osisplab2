#include "globals.h"

#include <cstdio>
#include <string.h>
#include <unistd.h>

int startChild(char* pathChild, char* pathEnv, unsigned indexChild);


int createChild(unsigned int indexChild, char* pathChildEnv, char* dirChild)
{
	printf("createChild ST\n");
	char	pathChild[256] = { 0, };
	pid_t	pid;

	sprintf(pathChild, "%s%s", dirChild, CHILD_NAME_PROGRAM);
	pid = fork();

	if (pid == -1)
	{
		printf("Error in fork(): %d\n", errno);
		return -1;
	}
	if (pid == 0)
	{
		startChild(pathChild, pathChildEnv, indexChild);
		return -1;
	}
	printf("createChild OK\n");

	return 0;
}

bool getvalue(char* env, const char* name, char** value)
{
	size_t sizeEnv = strlen(env);
	size_t sizeName = strlen(name);

	if (sizeEnv <= sizeName)
	{
		return false;
	}
	if (strncmp(env, name, sizeName) != 0)
	{
		return false;
	}

	if (env[sizeName] != '=')
	{
		return false;
	}
	*value = env + sizeName + 1;
	printf("value=%s\n", *value);

	return true;
}

char* getenv(const char* name, char** arrayEnv)
{
	printf("getenv ST");
	char* value = NULL;

	while (*arrayEnv != NULL)
	{
		printf(">> %s\n", *arrayEnv);
		if (getvalue(*arrayEnv, name, &value))
		{
			printf("getenv OK");
			return value;
		}
		//if (strcoll(*arrayEnv, name) == 0)
		//{
		//	return *arrayEnv;
		//}
		arrayEnv++;
	}
	return NULL;
}

int createChild(unsigned int indexChild, char* pathChildEnv, char** arrayEnv)
{
	printf("createChild-2 ST\n");
	char* dirChild;

	dirChild = getenv(CHILD_DIR, arrayEnv);
	if (dirChild == NULL)
	{
		printf("createChild-2 OK error\n");
		return -1;
	}
	char	pathChild[256] = { 0, };
	pid_t	pid;

	sprintf(pathChild, "%s%s", dirChild, CHILD_NAME_PROGRAM);
	pid = fork();

	if (pid == -1)
	{
		printf("Error in fork(): %d\n", errno);
		return -1;
	}
	if (pid == 0)
	{
		startChild(pathChild, pathChildEnv, indexChild);
		return -1;
	}
	printf("createChild-2 OK\n");

	return 0;
}

int startChild(char* path, char* pathEnv, unsigned index)
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
