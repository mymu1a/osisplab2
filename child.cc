#include <cerrno>
#include <stdio.h>
#include <unistd.h>

//void printEnv(char* pathEnv);
void printEnv(char* envp[]);

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

//	printEnv(argv[1]);
	printEnv(&argv[1]);


	printf("child process OK\n\n");

	return 0;
}

//void printEnv(char* pathEnv)
//{
//	/// TODO
//}

void printEnv(char* envp[])
{


	for (int pointer = 0; envp[pointer] != 0; pointer++)
	{
		printf("%saaaaaaaaaaaaaaaaaaaaaaaaaa\n", envp[pointer]);
	}
}






//createChild ST
//createChild OK
//startChild ST
//Before exec child process
//child process ST
//Child program name : child_00
//Child program pid : 8226
//Child program parent pid : 8213
//Path to ChildEnv : childEnv.txt
//
//childEnv.txt//////////////////////////////////////////////////
//child process OK