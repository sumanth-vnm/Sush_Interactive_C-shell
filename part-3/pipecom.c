#include "headers.h"

void pipecom(char *d, char **arr, int comm, int temp_in, int temp_out, char *hist_comm, char *hist_path, char *buffer, char *buff)
{
    char *command = (char *)malloc(1000 * sizeof(char));
    strcpy(command, "");
    for (int i = 0; i < comm; i++)
    {
        strcat(command, arr[i]);
        strcat(command, " ");
    }
    char **newarr = (char **)malloc(100 * sizeof(char *));
    for (int i = 0; i < 100; i++)
    {
        newarr[i] = (char *)malloc(100 * sizeof(char));
    }
    int prev = 0, coun = 0;
    for (int i = 0; i < strlen(command); i++)
    {
        if (command[i] == '|')
        {
            strncpy(newarr[coun], command + prev, i - prev);
            prev = i + 1;
            coun++;
        }
    }
    strncpy(newarr[coun], command + prev, strlen(command) - prev);
    coun++;
    int pipe_in, pipe_out;
    int ends[2];
    if (pipe(ends) < 0)
    {
        perror("could not create pipe");
    }
    pipe_in = ends[0];
    pipe_out = ends[1];
    int f;
    int status;
    for (int i = 0; i < coun; i++)
    {
        pipe(ends);
        f = fork();
        if (f == 0)
        {
            if(i==coun-1){
                if(dup2(temp_out,1)<0){
                    perror("Unable to create pipe");
                }
            }
            else{
                if(dup2(ends[1], 1)<0){
                    perror("There is an error in creating in out pipe");
                }
                close(ends[0]);
            }
            execute(newarr[i], hist_comm, hist_path, buffer, buff);
            exit(1);
        }
        else
        {
            waitpid(f, &status, 0);
            dup2(ends[0],0);
            close(ends[1]);
        }
    }
    dup2(temp_out, 1);
    dup2(temp_in, 0);
    
}