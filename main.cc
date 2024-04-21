#include <cerrno>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*
* в окружении создается переменная среды CHILD_PATH с именем каталога, где находится программа child
* 
* родительскому процессу как `параметр командной строки` передается файл
*/
#define CHILD_NAME_PROGRAM "child"
#define CHILD_DIR "CHILD_PATH"

int createChild(char* pathChild, unsigned indexChild, char* pathChildEnv);
void printEnv(char* envp[]);
void printUsage(char* nameProgram);


int main(int argc, char* argv[], char* envp[])
{
	printf("main ST\n");
	if (argc < 2)
	{
		printUsage(argv[0]);
		printf("main OK\n");
		return 1;
	}
	char* dirChild;

	dirChild = "./"; // getenv(CHILD_DIR);
	if (dirChild == NULL)
	{
		printUsage(argv[0]);
		printf("main OK\n");
		return 1;
	}
	printf("Parent program name: %s\n", argv[0]);
	printf("Parent program pid: %d\n", getpid());
	printf("Path to ChildEnv: %s\n", argv[1]);
	printf("\n");

	printEnv(envp);

	char ch;
	unsigned indexChild = 0;
	char pathChild[256] = { 0, };

	sprintf(pathChild, "%s%s", dirChild, CHILD_NAME_PROGRAM);

	while (ch = getchar())
	{
		switch (ch)
		{
		case '+':
			if (createChild(pathChild, indexChild++, argv[1]) == -1)
			{ // child or error
				return 0;
			}
			// parent process
			break;
		case 'q':
			printf("main OK\n");
			return 0;
		}
	}
	printf("main OK\n");

	return 0;
}

void printUsage(char* nameProgram)
{
	printf("Usage: \n"
		"1. Set Environment variable: %s\n"
		"2. %s <file-child-env>\n"
		, CHILD_DIR, nameProgram);
}

void printEnv(char* envp[])
{
	for (int index = 0; envp[index] != 0; index++)
	{
		printf("%s\n", envp[index]);
	}
}

