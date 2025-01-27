# include "headers.h"

int delete_comm(int f,char * hist_path,char *hist_comm){
    if(f<0){
        perror("File");
    }
    char *temp=(char *)malloc(100*sizeof(char));
    strcpy(temp,getenv("HOME"));
    strcat(temp,"histtemp.txt");
    char *buffer=(char *)malloc(500*5*sizeof(char));
    struct stat st;
    stat(hist_path,&st);
    long long file_size= st.st_size;
    long long start=0;
    int i=1;
    start=500*i;
    lseek(f,500,SEEK_SET);
    read(f,buffer,500*19);
    int f1=open(hist_path,O_RDWR|O_CREAT);
    lseek(f1,0,SEEK_SET);
    write(f1,buffer,500*19);
    lseek(f1,500*4,SEEK_SET);
    write(f1,hist_comm,500);
    close(f1);
    return 1;
}