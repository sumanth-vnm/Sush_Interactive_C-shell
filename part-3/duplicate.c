#include "headers.h"

void syscom(char *c, char **arr, int comm)
{
    char *command;
    strcpy(command, c);
    char **args;
    int x = 111;
    args = (char **)malloc((comm + 1) * sizeof(char **));
    int count = 0;
    int flag=0;
    for (int j = 0; j < comm; j++)
    {
        if (strcmp(arr[j], "&") != 0)
        {
            flag=1;
            args[count++] = arr[j];
            
        }
    }
    args[count] = NULL;
    int status;
    if (comm <1)
    {
        printf("Invalid no of arguments\n");
    }
    else
    {
        if (flag == 1)
        {
            if (strcmp(arr[2], "&") == 0)
            {
                //background process
                x = fork();
                if (x == 0)
                {
                    setpgid(0,0);
                    execvp(args[0], args);
                }
            }
            else if (strcmp(arr[1], "&") == 0)
            {
                //backgorund process
                x = fork();
                if (x == 0)
                {
                    setpgid(0,0);
                    execvp(args[0], args);
                }
            }
            else
            {
                //fore ground process
                x = fork();
                if (x == 0)
                {
                    execvp(args[0], args);
                }
                else
                {
                    waitpid(x,&status,0);
                }
            }
        }
        else if (comm == 2)
        {
            if (strcmp(arr[1], "&") == 0)
            {
                //background process
                x = fork();
                if (x == 0)
                {
                    setpgid(0,0);
                    //printf("this is execvp command");
                    execvp(args[0], args);
                }
            }
            else
            {
                //foreground process
                x = fork();
                printf("%d", x);
                if (x == 0)
                {
                    execvp(args[0], args);
                }
                else
                {
                    waitpid(x,&status,0);
                }
            }
        }
        else
        {
            x = fork();
            if (x == 0)
            {
                execvp(args[0], args);
            }
            else
            {
                waitpid(x,&status,0);
            }
            //foreground  process
        }
    }
}
