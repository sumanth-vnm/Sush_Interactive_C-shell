**Code Structure**

    ├─ a.out
    ├─ bg.c
    ├─ cd.c
    ├─ delete_comm.c
    ├─ duplicate.c
    ├─ echo.c
    ├─ fg.c
    ├─ headers.h
    ├─ history.c
    ├─ jobs.c
    ├─ ls.c
    ├─ main.c
    ├─ makefile
    ├─ pinfo.c
    ├─ pipecom.c
    ├─ prompt.c
    ├─ prompt.h
    ├─ pwd.c
    ├─ repeat.c
    ├─ replay.c
    ├─ signals.c
    ├─ split.c
    └─ syscom.c

**How to run ?**: compile  the make file in the dircetory which compiles all the files required for the project and then execute ./a.out(in linux).

**Commands implemented:**

- **cd:** Changes the current directory (implmented with special flags like ~,-). Implemented in cd.c

- **echo:** Outputs/prints the given arguments to the terminal. Implemented in echo.c

- **pwd:** Outputs/prints the current working directory to the terminal. Implemented in pwd.c

- **ls:** Lists the contents of the directory (implemented with various flags like 
    - -l :long contents which displays variety of details regarding the files
    - -a :displays even hidden files
    - -la: long and hidden files
    - -l {dir} -a {dir} ,etc:

    Implemented in ls.c


- **System commands:** Systems commands can be executed within background or foreground using & flag. Eg:
    - gedit & runs in background
    - gedit runs in foreground
Implemented in syscom.c


- **pinfo:** pinfo command is used for displaying process information .displays the info of calling process by default and displays the info of the pid when argument pid is passed.Implemented in pinfo.c

- **repeat:** Repeats a command for n number of times .Implemented in repeat.c

- **history:** Outputs the history of commands typed in(default no of commands outputed =20).Implemented in history.txt

- **Note:** the history command leads to create a directory in the home directory with file name as history.txt.

- **Input/output redirection:**
The shell can handle both input and output redirection individually and simultaneously as well. Implemented in main.c
    -  "<"  for Inpu redirection
    - ">" for output redirection(writes the file given in argument) . 
    - ">>" for output redirection appends to the file given in argument.


- **piping:** The shell can handle pipe commands (i.e, output of one pipe is sent as input to anothe pipe) seperated by "|" . The program can even handle the cases where input and output redirection commands are given in pipe commands .Implemented in pipecom.c

- **jobs:** prints the current jobs in the background with theire status and pid and job number.Implemented in jobs.c(implemented with flags -r, -s).

- **bg** Brings a stopped background process to running status.Implemented in bg.c

- **fg** Brings a running/stopped background process to foreground.implemented in fg.c.

- **sig** Passes a specified signal to the specified job number. Implemented in signals.c

- **signal handling:**
    - **ctrl-z:** stops the current executing foreground process without stopping the parent shell process.

    - **ctrl-c:** Interrupts the current executing foreground process without interrupting the parent shell process.

    - **ctrl-d:** Terminated the shell without causing distubance to the original terminal.

- **replay:** replay a command for every given amount of seconds and till upto a finite number of given seconds.Implemented in replay.c










