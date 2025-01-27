#include "headers.h"

void pinfo(char *d ,char **arr,int comm){
    int pid;
    if(comm==1){
        pid=getpid();
    }
    else if(comm==2){
        sscanf(arr[1],"%d",&pid);
    }
    else{
        perror("Invalid no of arguments");
    }
    char procexe[100];
    char procpath[100];
    sprintf(procpath,"/proc/%d/status",pid);
    sprintf(procexe,"/proc/%d/exe",pid);
    
    char file[1000];
    int file_size=1000;
    FILE * f1=fopen(procpath,"r");
    int f = open(procpath, O_RDONLY); 
    if(f<0){
        printf("\n Unable to open : %s ", procpath);
    }
    char status[100];
    int flag=1;
    int count=0;
    char buff[1000];
    char memory[64];
    char state[64];
    char  empty[]="";
    while(read(f,&buff[count],1)==1){
        if(buff[count]=='\n' || count==999){
            buff[count]='\0';
            if(strncmp(buff,"State",5)==0){
                strcpy(state,buff+6);
            }
           if(strncmp(buff,"VmSize",6)==0){
                strcpy(memory,buff+7);
           }
            count=-1;
        }
        count++;
    }
    
    int i=0,j=0;
    while(state[i]==' ' || state[i]=='\t'){
        i++;
    }

    while(memory[j]==' ' || memory[j]=='\t'){
        j++;
    }
    strcpy(state,state+i);
    state[1]='\0';
    strcpy(memory,memory+j);
    memory[strlen(memory)-3]='\0';
    int curr=getpid();
    int arg=getpgid(pid);
    int curr_grp=getpgid(curr);
    if(arg==curr_grp){
        strcat(state,"+");
    }
    char buffer[100];
    ssize_t length=readlink(procexe,buffer,100);
    buffer[length]='\0';

    //pid
    printf("pid -- %d\n",pid);
    //state
    printf("Process Status -- %s\n",state);
    //memory
    printf("memory -- %s\n",memory);
    //exe
    printf("Executable Path -- %s\n",buffer);
    close(f);
    fclose(f1);
}



void pinfo_status(char *d ,int process,int comm,char *state){
    int pid=process;
    char procexe[100];
    char procpath[100];
    sprintf(procpath,"/proc/%d/status",pid);
    sprintf(procexe,"/proc/%d/exe",pid);
    
    char file[1000];
    int file_size=1000;
    int f = open(procpath, O_RDONLY); 
    if(f<0){
        strcpy(state,"E");
    }
    char status[100];
    int flag=1;
    int count=0;
    char buff[1000];
    char memory[64];
    char  empty[]="";
    while(read(f,&buff[count],1)==1){
        if(buff[count]=='\n' || count==999){
            buff[count]='\0';
            if(strncmp(buff,"State",5)==0){
                strcpy(state,buff+6);
            }
           if(strncmp(buff,"VmSize",6)==0){
                strcpy(memory,buff+7);
           }
            count=-1;
        }
        count++;
    }
    
    int i=0,j=0;
    while(state[i]==' ' || state[i]=='\t'){
        i++;
    }

    while(memory[j]==' ' || memory[j]=='\t'){
        j++;
    }
    strcpy(state,state+i);
    state[1]='\0';
    strcpy(memory,memory+j);
    memory[strlen(memory)-3]='\0';
    int curr=getpid();
    int arg=getpgid(pid);
    int curr_grp=getpgid(curr);
    /*if(arg==curr_grp){
        strcat(state,"+");
    }
    char buffer[100];
    ssize_t length=readlink(procexe,buffer,100);
    buffer[length]='\0';*/

    //pid
    /*printf("pid -- %d\n",pid);
    //state
    printf("Process Status -- %s\n",state);
    //memory
    printf("memory -- %s\n",memory);
    //exe
    printf("Executable Path -- %s\n",buffer);*/
}