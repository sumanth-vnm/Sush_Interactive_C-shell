#include "headers.h"
extern gpid;




void fg(char *d, char **arr, int comm)
{
    int gp;
    int flag = 0;
    sscanf(arr[1], "%d", &gp);
    char *status=(char *)malloc(50*sizeof(char));
    for (int i = 0; i < b; i++)
    {
        if (gp == bp[i].seq)
        {
            pinfo_status(d,bp[i].pid,1,status);
            if(strcmp(status,"E")!=0){
                gpid = bp[i].pid;
                strcpy(fg_name,bp[i].name);
                flag = 1;
                fgp=gpid;
                printf("%s\n",bp[i].name);
                break;
            }
        }
    }
    if (flag == 0)
    {
        printf("No Job exists with the given no\n");
    }
    else
    {
        int dup_pid = getpgrp();
        signal(SIGTTIN, SIG_IGN);
        signal(SIGTTOU, SIG_IGN);
        tcsetpgrp(STDIN_FILENO, gpid);
        tcsetpgrp(STDOUT_FILENO,gpid);
        kill(gpid,SIGCONT);
        int status;
        waitpid(gpid, &status, WUNTRACED);
        tcsetpgrp(STDIN_FILENO, dup_pid);
        tcsetpgrp(STDOUT_FILENO, dup_pid);
        signal(SIGTTIN, SIG_DFL);
        signal(SIGTTOU, SIG_DFL);
        signal(SIGINT,SIG_DFL);
        signal(SIGTSTP,SIG_DFL);
    }
}