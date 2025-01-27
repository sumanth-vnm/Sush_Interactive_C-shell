#include "headers.h"

void replay(char *d, char **arr, int comm)
{
    if (comm <= 6)
    {
        printf("Invlaid no of arguments\n");
    }
    char **newarr = (char **)malloc(100 * sizeof(char *));
    for (int i = 0; i < 100; i++)
    {
        newarr[i] = (char *)malloc(100 * sizeof(char));
    }
    int c = 0;
    for (int i = 2; i < comm - 4; i++)
    {
        strcpy(newarr[i - 2], arr[i]);
        c++;
    }
    newarr[c] = NULL;
    if (c == 0)
    {
        printf("invalid no of arguments\n");
    }
    else
    {
        int rtime;
        if (sscanf(arr[comm - 3], "%d", &rtime) < 0)
        {
            perror("Invlaid command");
        }
        int endtime;
        if (sscanf(arr[comm - 1], "%d", &endtime) < 0)
        {
            perror("Invlaid command");
        }
        for (int i = 0; i < endtime/rtime; i++)
        {
            sleep(rtime);
            int f = fork();
            if (f == 0)
            {
                if(execvp(newarr[0],newarr)<0){
                    perror("invlaid command");
                }

            }
            else{
                waitpid(f,NULL,0);

            }
        }
    }
}