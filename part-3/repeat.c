#include "headers.h"

void repeat(char *c,char **arr, int comm){
    int no;
    sscanf(arr[1],"%d",&no);
    int x;
    int status;
    char  **args;
    args=(char **)malloc((comm-1)*sizeof(char *));
    for(int j=0;j<comm-2;j++){
        args[j]=arr[j+2];
    }
    args[comm-2]=NULL;
    for(int i=0;i<no;i++){
        x=fork();
        if(x==0){
            execvp(args[0],args);
        }
        waitpid(x,&status,0);
    }

}