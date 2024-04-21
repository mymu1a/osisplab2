#include <cerrno>
#include <stdio.h>
#include <unistd.h>

void printEnv(char* pathEnv);

/*
* При запуске дочернего процесса ему передается сокращенное окружение
* Набор переменных указывается в файле
*/
int main(int argc, char* argv[])
{
	printf("child process ST\n");
	if (argc < 2)
	{
		printf("Usage: %s <file-child-env>\n", argv[0]);
		printf("child process OK\n");
		return 1;
	}
	printf("Child program name: %s\n", argv[0]);
	printf("Child program pid: %d\n", getpid());
	printf("Child program parent pid: %d\n", getppid());
	printf("Path to ChildEnv: %s\n", argv[1]);
	printf("\n");

	printEnv(argv[1]);


	printf("child process OK\n\n");

	return 0;
}

void printEnv(char* pathEnv)
{
	FILE* pFile;
	
	pFile = fopen(pathEnv, "r");
	if (pFile == NULL)
	{
		return;
	}
	fclose(pFile);
}

