# 0x16. C - Simple Shell

Write a simple UNIX comman interpreter.

## Concepts:

This project focusses on the following concepts:

 - [Everything you need to know to start coding your own shell](https://intranet.alxswe.com/concepts/64)
 - [Approaching a Project](https://intranet.alxswe.com/concepts/350)

## Resources:

I have found the following resources to be particularly useful for this project (as well as the concepts listed in the section above):

 - [Unix shell](https://en.wikipedia.org/wiki/Unix_shell)
 - [Thompson shell](https://en.wikipedia.org/wiki/Thompson_shell)
 - [Ken Thompson](https://intranet.alxswe.com/rltoken/wTSu31ZP1f7fFTJFgRQC7w)
 - *Everything you need to know to start coding your own shell* concept page

## Requirements:

### General:

 - Allowed editors: `vi`, `vim`, `emacs`
 - All your files will be compiled on Ubuntu 20.04 LTS using `gcc`, using the options `-Wall -Werror -Wextra -pedantic -std=gnu89`
 - All your files should end with a new line
 - A `README.md` file, at the root of the folder of the project is mandatory
 - Your code should use the `Betty` style. It will be checked using `betty-style.pl` and `betty-doc.pl`
 - Your shell should not have any memory leaks
 - No more than 5 functions per file
 - All your header files should be include guarded
 - Use system calls only when you need to ([why?](https://www.quora.com/Why-are-system-calls-expensive-in-operating-systems))
 - Write a `README` with the description of your project
 - You should have an `AUTHORS` file at the root of your repository, listing all individuals having contributed content to the repository. Format, see [Docker](https://github.com/moby/moby/blob/master/AUTHORS)

### GitHub:

There should be one project repository per group. If you and your partner have a repository with the same name in both your accounts, you risk a 0% score. Add your partner as a collaborator.

## Tasks:

The following is a breakdown of all of the tasks for this project. The actual instructions for each task can be found on the relevant project page on the ALX SE Intranet, however, sharing that information is prohibited. I have therefore given a brief description of what each entails, what the code does and in some cases, I have included some extra information for context and learning (particularly the more advanced topics).

### Task 0 - Betty would be proud

Write a beautiful code that passes the Betty checks.

### Task 1 - Simple shell 0.1

Write a UNIX command line interpreter.

 - Usage: `simple_shell`

Your Shell should:

 - Display a prompt and wait for the user to type a command. A command line always ends with a new line.
 - The prompt is displayed again each time a command has been executed.
 - The command lines are simple, no semicolons, no pipes, no redirections or any other advanced features.
 - The command lines are made only of one word. No arguments will be passed to programs.
 - If an executable cannot be found, print an error message and display the prompt again.
 - Handle errors.
 - You have to handle the “end of file” condition (`Ctrl+D`)

You don’t have to:

 - use the `PATH`
 - implement built-ins
 - handle special characters: `\"`, `'`, ```, `\`, `*`, `&`, `#`
 - be able to move the cursor
 - handle commands with arguments

`execve` will be the core part of your Shell, don’t forget to pass the environ to it…

Example:

```
julien@ubuntu:~/shell$ ./shell
#cisfun$ ls
./shell: No such file or directory
#cisfun$ /bin/ls
barbie_j       env-main.c  exec.c  fork.c  pid.c  ppid.c    prompt   prompt.c  shell.c  stat.c         wait
env-environ.c  exec    fork    mypid   ppid   printenv  promptc  shell     stat test_scripting.sh  wait.c
#cisfun$ /bin/ls -l
./shell: No such file or directory
#cisfun$ ^[[D^[[D^[[D
./shell: No such file or directory
#cisfun$ ^[[C^[[C^[[C^[[C
./shell: No such file or directory
#cisfun$ exit
./shell: No such file or directory
#cisfun$ ^C
julien@ubuntu:~/shell$ echo "/bin/ls" | ./shell
barbie_j       env-main.c  exec.c  fork.c  pid.c  ppid.c    prompt   prompt.c  shell.c  stat.c         wait
env-environ.c  exec    fork    mypid   ppid   printenv  promptc  shell     stat test_scripting.sh  wait.c
#cisfun$ julien@ubuntu:~/shell$
```

### Task 2 Simple shell 0.2

Simple shell 0.1 +

 - Handle command lines with arguments

### Task 3 - Simple shell 0.3

Simple shell 0.2 +

 - Handle the `PATH`
 - `fork` must not be called if the command doesn’t exist

Example:

```
julien@ubuntu:~/shell$ ./shell_0.3
:) /bin/ls
barbie_j       env-main.c  exec.c  fork.c  pid.c  ppid.c    prompt   prompt.c  shell_0.3  stat    test_scripting.sh  wait.c
env-environ.c  exec    fork    mypid   ppid   printenv  promptc  shell     shell.c    stat.c  wait
:) ls
barbie_j       env-main.c  exec.c  fork.c  pid.c  ppid.c    prompt   prompt.c  shell_0.3  stat    test_scripting.sh  wait.c
env-environ.c  exec    fork    mypid   ppid   printenv  promptc  shell     shell.c    stat.c  wait
:) ls -l /tmp
total 20
-rw------- 1 julien julien    0 Dec  5 12:09 config-err-aAMZrR
drwx------ 3 root   root   4096 Dec  5 12:09 systemd-private-062a0eca7f2a44349733e78cb4abdff4-colord.service-V7DUzr
drwx------ 3 root   root   4096 Dec  5 12:09 systemd-private-062a0eca7f2a44349733e78cb4abdff4-rtkit-daemon.service-ANGvoV
drwx------ 3 root   root   4096 Dec  5 12:07 systemd-private-062a0eca7f2a44349733e78cb4abdff4-systemd-timesyncd.service-CdXUtH
-rw-rw-r-- 1 julien julien    0 Dec  5 12:09 unity_support_test.0
:) ^C
julien@ubuntu:~/shell$
```

### Task 4 - Simple shell 0.4

Simple shell 0.3 +

 - Implement the `exit` built-in, that exits the shell
 - Usage: `exit`
 - You don’t have to handle any argument to the built-in `exit`

### Task 5 - Simple shell 0.4

Simple shell 0.4 +

 - Implement the `env` *built-in*, that prints the current environment

Example:

```
julien@ubuntu:~/shell$ ./simple_shell
$ env
USER=julien
LANGUAGE=en_US
SESSION=ubuntu
COMPIZ_CONFIG_PROFILE=ubuntu
SHLVL=1
HOME=/home/julien
C_IS=Fun_:)
DESKTOP_SESSION=ubuntu
LOGNAME=julien
TERM=xterm-256color
PATH=/home/julien/bin:/home/julien/.local/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin
DISPLAY=:0
$ exit
julien@ubuntu:~/shell$
```
