#include "headers.h"


void pwd(char *c ){
    char pwd[100];
    getcwd(pwd,100);
    printf("%s\n",pwd);
}