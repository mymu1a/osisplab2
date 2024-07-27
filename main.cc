#include "globals.h"

#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

extern char** environ;

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

    while ((ch = getchar()) != 'q')
    {
        switch (ch) {
        case '+':
            if (createChild(indexChild++, argv[1], dirChild) == -1) {
                return 0;
            }
            break;
        case '*':
            if (createChild(indexChild++, argv[1], envp) == -1) {
                return 0;
            }
            break;
        case '&':
            if (createChild(indexChild++, argv[1], environ) == -1) {
                return 0;
            }
            break;
        case 'z':						// kill zombie processes
        {
            int stat;

            while (waitpid(-1, &stat, WUNTRACED) > 0)
            {
            }
            break;
        }
        }
    }
    printf("main OK\n");

    return 0;
}

void printUsage(char* nameProgram, short index) 
{
    printf("Usage: \n"
        "1. Set Environment variable: %s", CHILD_DIR);
    if (index == 1) {
        printf("\t\t<--");
    }
    printf("\n2. %s <file-child-env>", nameProgram);
    if (index == 2) {
        printf("\t\t<--");
    }
    printf("\n");
}

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