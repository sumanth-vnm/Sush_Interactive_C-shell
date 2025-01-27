#include "headers.h"

void echo(char *c,char **arr,int comm ){

    int i;
    for(i=1;i<comm;i++){
        printf("%s ",arr[i]);
    }
    printf("\n");
}