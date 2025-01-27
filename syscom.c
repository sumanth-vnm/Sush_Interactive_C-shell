#include "headers.h"
extern int* bgproc;
extern int proc;

void interrupt_handler(){
    if(fgp!=0){
        kill(fgp,SIGINT);
    }
    
}

void stop_handler(){
    if(fgp!=0){
        kill(fgp,SIGSTOP);
        printf("\n%s with process id %d is stopped\n",fg_name,fgp);
        strcpy(bp[b].name,fg_name);
        bp[b].pid=fgp;
        bp[b].seq=s+1;
        b++;
        s++;
        fgp=0;
    }
}

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
                setpgid(0,0);
                if(execvp(args[0], args)<0){
                    perror("Invalid Command");
                }
            }
            else{
                printf("Process id %d\n",x);
                bp[b].pid=x;
                strcpy(bp[b].name,args[0]);
                bp[b].seq=s+1;
                tcsetpgrp(STDIN_FILENO,getpgrp());
                tcsetpgrp(STDOUT_FILENO,getpgrp());
                s++;
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
                signal(SIGTSTP,stop_handler);
                signal(SIGINT,interrupt_handler);
                setpgid(0,0);
                fgp=x;
                strcpy(fg_name,arr[0]);
                if(fgp!=0){
                    waitpid(x, &status, WUNTRACED);
                }
                signal(SIGINT,SIG_IGN);
            }
        }
    }
}
