#include "headers.h"

void history(char *d,char **arr,int comm,int f,char *hist_path){

    struct stat st;
    if(f<0){
        perror("Unable to display history command");
    }
    stat(hist_path,&st);
    long long file_size=st.st_size;
    int start;
    int part;
    if(comm==1){
        part=20;
        start=file_size-(500*part);
        if(start<0){
            start=0;
        }
    }
    else{
        sscanf(arr[1],"%d",&part);
        start=file_size-(500*part);
        if(start<0){
            start=0;
        }
    }
    char *buffer=(char *)malloc(500*sizeof(char));
    int i=0;
    int block=500;
    int ind;
    while(start<file_size){
        lseek(f,start,SEEK_SET);
        read(f,buffer,500);
        for(int j=strlen(buffer)-1;j>=0;j--){
            if(buffer[j]!=' '){
                ind =j;
                break;
            }
        }
        buffer[ind+1]='\0';
        i+=1;
        printf("%s\n",buffer);
        start+=block;
    }
}