#include "prompt.h"
#include "headers.h"
extern char *path;
extern char *invoked;
extern char *user;
extern char *sysname;
void prompt() {
    int cmp;
    user=(char *)malloc(30*sizeof(char));
    user=getlogin();
    sysname=(char *)malloc(30*sizeof(char));
    gethostname(sysname,HOST_NAME_MAX+1);
    cmp=strncmp(path,invoked,strlen(invoked));
    if(cmp==0){
        path[strlen(path)]='\0';
        path+=strlen(invoked);
    }
    printf("%s@%s:~%s>",user,sysname,path);    
    
}
