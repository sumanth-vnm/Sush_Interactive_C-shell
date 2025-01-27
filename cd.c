#include "headers.h"
extern char *path;
extern char *invoked;
extern *prev;
void cd(char *c, char **arr, int comm)
{
    char *directory = (char *)malloc(300 * sizeof(char));
    int i = 0, j = 0;
    char temp[100];
    char d[100];

    if (comm == 1)
    {
        strcpy(temp,prev);
        strcpy(prev,getcwd(d,100));
        if (chdir(invoked)!= 0)
        {
            strcpy(prev,temp);
            perror("Directory");

            
        }
        else{
            char *wd = getcwd(d, 100);
            strcpy(path, wd);


        }
    }
    else if(strcmp(arr[1],"~")==0 || strcmp(arr[1],"")==0){
        strcpy(temp,prev);
        strcpy(prev,getcwd(d,100));
        if (chdir(invoked)!= 0)
        {
            strcpy(prev,temp);
            perror("Directory");
            
        }
        else{
            char *wd = getcwd(d, 100);
            strcpy(path, wd);

        }

    }
    else if(strcmp(arr[1],"-")==0){
        strcpy(temp,getcwd(d,100));

        if (chdir(prev)!= 0)
        {
            perror("Directory");
            
        }
        else{
            strcpy(prev,temp);
            char *wd = getcwd(d, 100);
            strcpy(path, wd);

        }

    }
    
    else if(comm>2){
        printf("Invalid no of aguments\n");
    }
    else

    {
        strcpy(directory, arr[1]);
        strcpy(temp,prev);
        strcpy(prev,getcwd(d,100));
        if (chdir(directory) != 0)
        {
            strcpy(prev,temp);
            perror("Directory");
        }
        else
        {
            char *wd = getcwd(d, 100);
            strcpy(path, wd);
        }
    }
}