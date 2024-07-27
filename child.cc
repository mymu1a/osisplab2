#include <cerrno>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

void printEnv(const char* pathEnv);

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

    for (int i = 0; i < argc; i++)
    {
        printf("argv[%d]: %s\n", i, argv[i]);
    }

    printEnv(argv[1]);

    printf("child process OK\n\n");

    return 0;
}

void printEnv(const char* pathEnv) 
{
    FILE* pFile;
    pFile = fopen(pathEnv, "r");
    if (pFile == NULL) {
        perror("Error opening file");
        return;
    }
    printf("file is open\n");

    char env_var_name[128];
    char* env_var_value;
    while (fscanf(pFile, "%127s", env_var_name) != EOF) 
    {
//        printf("in while, env_var_name=%s\n", env_var_name);
        env_var_value = getenv(env_var_name);
        if (env_var_value) 
        {
            printf("%s: %s\n", env_var_name, env_var_value);
        }
        else 
        {
            printf("%s: value wasn't found\n", env_var_name);
        }
    }

    printf("close file\n");
    fclose(pFile);
}