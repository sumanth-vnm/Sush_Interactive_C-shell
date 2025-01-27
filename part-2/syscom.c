#include "headers.h"
extern int* bgproc;
extern int proc;

void syscom(char *c, char **arr, int comm,int f)
{
    char *command;
    strcpy(command, c);
    char **args;
    pid_t x = 111;
    args = (char **)malloc((comm + 1) * sizeof(char **));
    int count = 0;
    int flag = 0;
    for (int j = 0; j < comm; j++)
    {
        if (strcmp(arr[j], "&") != 0)
        {
            args[count++] = arr[j];
        }
        else{
            flag=1;
        }
    }
    args[count] = NULL;
    int status;
    if (comm < 1)
    {
        perror("Invalid no of arguments\n");
    }
    else
    {
        if (flag == 1)
        {
            //background process
            x = fork();
            if (x == 0)
            {
                setpgid(0, 0);
                if(execvp(args[0], args)<0){
                    perror("Invalid Command");
                }
                exit(0);
            }
            else{
                printf("Process id %d\n",x);
                bp[b].pid=x;
                bp[b].name=args[0];
                b++;
            }
        }
        else
        {
            //foreground process
            x = fork();
            if (x == 0)
            {
                if(execvp(args[0], args)<0){
                    perror("Invalid Command");
                }
            }
            else
            {
                waitpid(x, &status, 0);
            }
        }
    }
}
