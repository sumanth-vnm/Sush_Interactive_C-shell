#include <stdio.h>    
#include <unistd.h>
#include<stdlib.h>
#include <fcntl.h>
#include<limits.h>
#include<string.h>
#include <dirent.h>
#include<sys/stat.h>
#include<sys/wait.h>


struct bg_proc{
    int pid;
    char* name;
};

struct bg_proc bp[100];

int b;

struct exit_proc{
    int status;
    int pid;
    char* name;
};
int mem;

