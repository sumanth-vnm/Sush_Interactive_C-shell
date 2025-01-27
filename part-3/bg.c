#include "headers.h"

void bg(char *d,char **arr,int comm){
    char* state=(char *)malloc(50^sizeof(char));
    int num;
    int flag=0;
    sscanf(arr[1],"%d",&num);
    if(comm!=2){
        printf("Invalid no of arguments\n");
    }
    else{
        for(int i=0;i<b;i++){
            if(bp[i].seq==num){
                pinfo_status(d,bp[i].pid,1,state);
                if(strcmp(state,"T")==0){
                    kill(bp[i].pid,SIGCONT);
                    printf("[%d] %s running in background\n",bp[i].seq,bp[i].name);
                }
                flag=1;
            }
        }
        if(flag==0){
            printf("NO job exists with the given Job no\n");
        }
    }
}