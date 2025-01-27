#include "headers.h"

char *path;
char *invoked;
int *bgproc;
int proc;
char *user;
char *sysname;
char *prev;
int f;

struct bg_proc bp[100];
b = 0;

struct exit_proc ep[100];
mem = 0;

void exitted()
{
    int status;
    int x = waitpid(-1, &status, WNOHANG);
    for (int j = 0; j < b; j++)
    {
        if (x == bp[j].pid)
        {
            ep[mem].pid = x;
            ep[mem].status = status;
            ep[mem].name = bp[j].name;
            mem++;
            break;
        }
    }
    check_exitted();
    /*if(x>0){
        printf("Process %d exitted succesfully\n",x);
        if(WIFEXITED(status)){
            printf("Exitted normally\n");
        }
        else{
            printf("Exitted abnormally\n");
        }
    }*/
}

void check_exitted()
{
    char *sta;
    char *finished;
    finished = (char *)malloc(200 * sizeof(char));
    if (mem != 0)
    {
        printf("\n");
    }
    sta = (char *)malloc(20 * sizeof(char));
    for (int i = 0; i < mem; i++)
    {
        sta = (WIFEXITED(ep[i].status)) ? strcpy(sta, "Normally") : strcpy(sta, "Abnormally");
        sprintf(finished, "%s with pid %d exited %s\n%s@%s:~%s>", ep[i].name, ep[i].pid, sta, user, sysname, path);
        write(1, finished, strlen(finished));
    }
    mem = 0;
}
int main()
{
    prev = (char *)malloc(200 * sizeof(char));
    char *hist_path = (char *)malloc(100 * sizeof(char));
    strcpy(hist_path, getenv("HOME"));
    struct stat st;
    strcat(hist_path, "/history2021121005osn.txt");
    f = open(hist_path, O_RDWR | O_CREAT | O_RDONLY);
    chmod(hist_path, S_IRWXU);
    invoked = (char *)malloc(200 * sizeof(char));
    path = (char *)malloc(200 * sizeof(char));
    char initial[100];
    getcwd(initial, 100);

    strcpy(path, initial);
    strcpy(invoked, initial);
    proc = 0;
    //signal(SIGTSTP,NULL);
    //signal(SIGCONT,NULL);
    signal(SIGCHLD, exitted);
    bgproc = (int *)malloc(1000 * sizeof(int));
    char *buff = (char *)malloc(501 * sizeof(char));
    char *hist_comm = (char *)malloc(501 * sizeof(char));
    char *buffer = (char *)malloc(501 * sizeof(char));

    while (1)
    {
        prompt();
        size_t size = 200;
        char c[1000];
        char *d;
        d = (char *)malloc(1000 * sizeof(int));
        char **arr2 = (char **)malloc(100 * sizeof(char *));
        ;
        for (int i = 0; i < 100; i++)
        {
            arr2[i] = (char *)malloc(100 * sizeof(char));
        }
        gets(c);
        char **arr = (char **)malloc(100 * sizeof(char *));
        int i = 0;
        for (int i = 0; i < 100; i++)
        {
            arr[i] = (char *)malloc(100 * sizeof(char));
        }
        strcpy(d, c);
        int comm = split(c, arr);
        if (comm == 1 && strlen(arr[0]) == 0)
        {
            continue;
        }
        int temp_out=dup(STDOUT_FILENO);
        int brea = 0;
        int or = -1, direct_flag = 0;
        char fn[100];
        int paired_o=0;
        int paired_i=0;
        //dup2(STDOUT_FILENO, temp_out);
        for (brea = 0; brea < comm; brea++)
        {
            if (arr[brea][0] == '>')
            {
                direct_flag = 1;
                if (strlen(arr[brea]) == 1)
                {
                    strcpy(fn, arr[brea + 1]);
                    or = open(fn, O_WRONLY | O_CREAT, 0644);
                }
                else
                {
                    (arr[brea][1] == '>') ? strcpy(fn, arr[brea] + 2) : strcpy(fn, (arr[brea] + 1));
                    if (arr[brea][1] == '>')
                    {
                        if (strlen(arr[brea]) == 2)
                        {
                            or = open(arr[brea + 1], O_WRONLY | O_APPEND | O_CREAT, 0644);
                        }
                        else
                        {
                            paired_o=1;
                            or = open(fn, O_WRONLY | O_APPEND | O_CREAT, 0644);
                        }
                    }
                    else
                    {
                        paired_o=1;
                        or = open(fn, O_WRONLY | O_CREAT, 0644);
                    }
                }
                break;
            }
        }
        int temp_in=dup(STDIN_FILENO);
        int brea2 = 0;
        int direct_flag2 = 0;
        int ir = -1;

        for (brea2 = 0; brea2 < comm; brea2++)
        {
            if (arr[brea2][0] == '<')
            {
                direct_flag2 = 1;

                if (strlen(arr[brea2]) == 1)
                {
                    ir = open(arr[brea2 + 1], O_RDONLY);
                }
                else
                {
                    paired_i=1;
                    ir = open(arr[brea2] + 1, O_RDONLY);
                }
                break;
            }
        }
        if (direct_flag2 == 1)
        {
            
            if (ir < 0)
            {
                perror("Unable to open file");
            }
            if (dup2(ir,0) < 0)
            {
                perror("Unable to open file");
            }
        }
        int stop;

        /*if (direct_flag == 1 && direct_flag2 == 1)
        {
            stop = (brea2 > brea) ? brea : brea2;
        }
        else if (direct_flag == 1)
        {
            stop = brea;
        }
        else if (direct_flag2 == 1)
        {
            stop = brea2;
        }
        else
        {
            stop = (brea2 > brea) ? brea2 : brea;
        }*/

        if (direct_flag == 1)
        {
            if (or < 0)
            {
                perror("unable to open the file\n");
            }
            if (dup2(or, STDOUT_FILENO) < 0)
            {
                perror("Unable to duplicate file descriptor.");
                exit(1);
            }
        }
        int brea_end,brea_end2;
        brea_end=(paired_o)?brea:brea+1;
        brea_end2=(paired_i)?brea2:brea2+1;

        brea_end2=(brea_end2>comm)?comm:brea_end2;
        brea_end=(brea_end>comm)?comm:brea_end;
        int count=0;
        if(brea<brea2){
            for(int i=0;i<brea;i++){
                strcpy(arr2[count++],arr[i]);
            }
            for(int i=brea_end+1;i<brea_end2;i++){
                strcpy(arr2[count++],arr[i]);
            }
            for(int i=brea_end2;i<comm;i++){
                strcpy(arr2[count++],arr[i]);
            }

        }
        else{
            for(int i=0;i<brea2;i++){
                strcpy(arr2[count++],arr[i]);
            }
            for(int i=brea_end2+1;i<brea_end;i++){
                strcpy(arr2[count++],arr[i]);
            }
            for(int i=brea_end;i<comm;i++){
                strcpy(arr2[count++],arr[i]);
            }

        }
        //printf("%d %d %d %d %d\n",comm,direct_flag2,direct_flag,!(paired_i),!(paired_o));
        stop=comm-(direct_flag2+direct_flag+(!(paired_i)&&(direct_flag2))+(!(paired_o)&&direct_flag));
        sprintf(hist_comm, "%*s", -500, d);
        strcat(hist_comm, "\n");
        stat(hist_path, &st);
        long long file_size = st.st_size;
        lseek(f, file_size - 500, SEEK_SET);
        read(f, buffer, 500);
        sprintf(buff, "%*s", -500, buffer);
        strcat(buff, "\n");
        int k;


        if (strncmp(buff, hist_comm, 500) != 0)
        {
            lseek(f, file_size, SEEK_SET);
            write(f, hist_comm, 500);
        }
        if (comm == 0 || stop == 0)
        {
            if(direct_flag==1)
                dup2(temp_out, 1);
            if(direct_flag2==1)
                dup2(temp_in,0);
            continue;
        }
        else if (strcmp(arr2[0], "cd") == 0)
            cd(d, arr2, stop);
        else if (strcmp(arr2[0], "echo") == 0)
            echo(d, arr2, stop);
        else if (strcmp(arr2[0], "pwd") == 0)
            pwd(d, arr2, stop);
        else if (strcmp(arr2[0], "ls") == 0)
        {
            ls(d, arr2, stop);
        }
        else if (strcmp(arr2[0], "pinfo") == 0)
        {
            pinfo(d, arr2, stop);
        }
        else if (strcmp(arr2[0], "repeat") == 0)
        {
            repeat(d, arr2, stop);
        }
        else if (strcmp(arr2[0], "history") == 0)
        {
            history(d, arr2, stop, f, hist_path);
        }
        else if (strcmp(arr2[0], "exit") == 0)
        {
            break;
        }
        else
        {
            syscom(d, arr2, stop, f);
        }
        if(direct_flag==1)
            dup2(temp_out, 1);
        if(direct_flag2==1)
            dup2(temp_in, 0);
        free(arr);
        free(arr2);
    }
    close(f);
}
