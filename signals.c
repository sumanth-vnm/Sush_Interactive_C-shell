# include "headers.h"

void signals(char *d ,char **arr,int comm){
    if(comm!=3){
        perror("Invlaid no of arguments");
    }
    int num;
    sscanf(arr[2],"%d",&num);
    int job;
    int flag=0;
    sscanf(arr[1],"%d",&job);
    for(int i=0;i<b;i++){
        if(bp[i].seq==job){
            kill(bp[i].pid,num);
            flag=1;
        }
    }
    if(flag==0){
        perror("No job found\n");
    }
    
}