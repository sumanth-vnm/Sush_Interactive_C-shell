#include <stdio.h>    
#include <unistd.h>
#include<stdlib.h>
#include <fcntl.h>
#include<limits.h>
#include<string.h>
#include <dirent.h>
#include<sys/stat.h>
#include<sys/wait.h>
#include<errno.h>


struct bg_proc{
    int pid;
    char name[100];
    int seq;
};

struct bg_proc bp[1000];

int b;
int s;

struct exit_proc{
    int status;
    int pid;
    char name[100];
    int num;
};
int mem;

int fgp;
char* fg_name;

char dup_name[50];
int prompted;



