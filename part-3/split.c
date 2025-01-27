#include "headers.h"

int split(char *c, char **comm)
{
    char *command = (char *)malloc(300 * sizeof(char));
    command = c;
    char *temp = (char *)malloc(300 * sizeof(char));
    int i = 0, j = 0;
    int k = 0;
    while (i < strlen(command))
    {
        if ((command[i] == ' ' || command[i] == '\t')) 
        {
            if (i != j)
            {
                strcpy(comm[k], command + j);
                comm[k][i - j] = '\0';
                k++;
            }
            while (command[i] == ' ' || command[i] == '\t')
            {
                ++i;
            }
            j = i;
        }
        else
        {
            ++i;
        }
    }
    if(command[i-1]!=' ' && command[i-1]!='\t'){
        strcpy(comm[k], command + j);
        comm[k][i - j] = '\0';
        k++;
    }
    return k;
}