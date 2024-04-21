#include "globals.h"

#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


/*
* в окружении создается переменная среды CHILD_PATH с именем каталога, где находится программа child
* 
* родительскому процессу как `параметр командной строки` передается файл
*/
int createChild(unsigned indexChild, char* pathChildEnv, char* dirChild);
int createChild(unsigned indexChild, char* pathChildEnv, char** arrayEnv);
void printEnv(char* envp[]);
void printUsage(char* nameProgram, short index);


int main(int argc, char* argv[], char* envp[])
{
	printf("main ST\n");
	if (argc < 2)
	{
		printUsage(argv[0], 2);
		printf("main OK\n");
		return 1;
	}
	char* dirChild;

	dirChild = getenv(CHILD_DIR);
	if (dirChild == NULL)
	{
		printUsage(argv[0], 1);
		printf("main OK\n");
		return 1;
	}
	printf("Parent program name: %s\n", argv[0]);
	printf("Parent program pid: %d\n", getpid());
	printf("Path to ChildEnv: %s\n", argv[1]);
	printf("\n");

	printEnv(envp);
	printf("\n");
	printf("Type: + & * q\n");

	char ch;
	unsigned indexChild = 0;

	while (ch = getchar())
	{
		switch (ch)
		{
		case '+':
			if (createChild(indexChild++, argv[1], dirChild) == -1)
			{ // child or error
				return 0;
			}
			// parent process
		break;
		case '*':
			if (createChild(indexChild++, argv[1], envp) == -1)
			{ // child or error
				return 0;
			}
			// parent process
			break;
		case '&':
			if (createChild(indexChild++, argv[1], environ) == -1)
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

void printUsage(char* nameProgram, short index)
{
	printf("Usage: \n"
		"1. Set Environment variable: %s", CHILD_DIR);
	
	if (index == 1)
	{
		printf("\t\t<--");
	}
	printf("\n");
	printf("2. %s <file-child-env>", nameProgram);
	if (index == 2)
	{
		printf("\t\t<--");
	}
	printf("\n");
}

// is called with two arguments that point to the objects being compared
int comparator(const void* str1, const void* str2)
{
	return strcoll(*(char**)str1, *(char**)str2);
}

void sortEnv(char* envp[])
{
	int count = 0;
	char** base = envp;

	while (*envp++ != NULL)
	{
		count++;
	}
	printf("count=%d\n", count);
	qsort(base, count, sizeof(void*), comparator);
}

void printEnv(char* envp[])
{
	char* localePrev = setlocale(LC_COLLATE, LOCALE);
	if (localePrev == NULL)
	{
		printf("Error: cannot change locale to '%s'\n", LOCALE);
	}
	sortEnv(envp);
	setlocale(LC_COLLATE, localePrev);

	for (int index = 0; envp[index] != 0; index++)
	{
		printf("%s\n", envp[index]);
	}
}
