#include "headers.h"
#include<time.h>
#include<pwd.h>
#include<math.h>
extern char *invoked;

char* dateformat(char* s, time_t v)
{
        strftime(s, 36, "%d.%m.%Y %H:%M:%S", localtime(&v));
        return s;
}

void permissions(char *dir, char *permission ){
    struct stat st;
    stat(dir,&st);
    permission[0]=S_ISREG(st.st_mode)?'-':'d';
    permission[1]=(st.st_mode & S_IRUSR) > 0 ? 'r' : '-';
    permission[2]=(st.st_mode & S_IWUSR) > 0 ? 'w' : '-';
    permission[3]=(st.st_mode & S_IXUSR) > 0 ? 'x' : '-';
    permission[4]=(st.st_mode & S_IRGRP) > 0 ? 'r' : '-';
    permission[5]=(st.st_mode & S_IWGRP) > 0 ? 'w' : '-';
    permission[6]=(st.st_mode & S_IXGRP) > 0 ? 'x' : '-';
    permission[7]=(st.st_mode & S_IROTH) > 0 ? 'r' : '-';
    permission[8]=(st.st_mode & S_IWOTH) > 0 ? 'w' : '-';
    permission[9]=(st.st_mode & S_IXOTH) > 0 ? 'x' : '-';
    permission[10]='\0';
}

void display(int lf,int af,char * dir){

    struct dirent *s;
    struct stat st;
    struct passwd *pd;
    struct passwd *gd;
    char emp[10];
    char siz[64];
    DIR *di=opendir(dir);
    printf("%s:\n",dir);
    char temp[200];
    stat(dir,&st);
    long tot=0;
    getcwd(temp,200);
    if(chdir(dir)!=0){
        perror("Directory");
    }
    long high=0;
    int high1;
    int curr=0,curr1=0;
    char dat[36];
    long nlik=0;
    while ((s = readdir(di)) != NULL){
        stat(s->d_name,&st);
        if(S_ISREG(st.st_mode));
            tot+=st.st_size;
            pd=getpwuid(st.st_uid);
            gd=getpwuid(st.st_gid);
            if(st.st_size>=high){
                high=st.st_size;
            }
            if(strlen(pd->pw_name)>=curr){
                curr=strlen(pd->pw_name);
            }
            if(strlen(gd->pw_name)>=curr1){
                curr1=strlen(gd->pw_name);
            }
            if(st.st_nlink>=nlik){
                nlik=st.st_nlink;
            }
    }
    char links[64];
    sprintf(links,"%ld",nlik);
    int lsize=strlen(links);
    char highs[100];
    sprintf(highs,"%ld",high);
    high1=strlen(highs);
    printf("total %ld\n",tot/1024);
    DIR *di2=opendir(dir);

    while ((s = readdir(di2)) != NULL){
        stat(s->d_name,&st);
        if (!(af) && s->d_name[0] == '.')
            continue;
        if(lf){
            pd=getpwuid(st.st_uid);
            gd=getpwuid(st.st_gid);
            permissions(s->d_name,emp);
            printf("%s ",emp);
            printf("%*ld",-lsize-2,st.st_nlink);printf("%*s",-curr-2,pd->pw_name);printf("%*s",-curr1-2,gd->pw_name);
            printf("%*ld",-high1-2,st.st_size);printf(" %s ",dateformat(dat,st.st_mtime));
            printf("%s\n",s->d_name);
            //printf("%ld %s %s %ld %s %s \n",st.st_nlink, pd->pw_name, gd->pw_name, st.st_size,dateformat(dat,st.st_mtime),s->d_name);
        }

        else{
            printf("%s\n", s->d_name);
        }
    }
    chdir(temp);
    printf("\n");
}
void ls(char *c,char **arr,int comm ){
    char dir[200];
    getcwd(dir,200);
    char temp[200];
    int lf=0;
    int af=0,count;
    if(comm==1){
        lf=0;
        af=0;
    }
    int i=1;
    while(i<comm){
        if(arr[i][0]=='-'){
            if(strcmp(arr[i],"-a")==0){
                af=1;
            }
            if(strcmp(arr[i],"-l")==0){
                lf=1;
            }
            if(strcmp(arr[i],"-al")==0 || strcmp(arr[i],"-la")==0){
                af=1;lf=1;
            }
        }
        i++; 
    }
    i=1,count=0;
    while(i<comm){
        if(arr[i][0]!='-'){
            if(strcmp(arr[i],"~")==0){
                strcpy(temp,invoked);
                display(lf,af,temp);
                count++;
                break;
            }
            strcpy(temp,dir);
            strcat(temp,"/");
            strcat(temp,arr[i]);
            display(lf,af,temp);
            count++;
        }
        i++;
    }
    (count==0)?display(lf,af,dir):count+0;

}