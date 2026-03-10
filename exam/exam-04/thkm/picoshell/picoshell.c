/*
Assignment name:	picoshell
Expected files:		picoshell.c
Allowed functions:	close, fork, wait, exit, execvp, dup2, pipe
___________________________________________________________________

Write the following function:

int    picoshell(char **cmds[]);

The goal of this function is to execute a pipeline. It must execute each
commands [sic] of cmds and connect the output of one to the input of the
next command (just like a shell).

Cmds contains a null-terminated list of valid commands. Each rows [sic]
of cmds are an argv array directly usable for a call to execvp. The first
arguments [sic] of each command is the command name or path and can be passed
directly as the first argument of execvp.

If any error occur [sic], The function must return 1 (you must of course
close all the open fds before). otherwise the function must wait all child
processes and return 0. You will find in this directory a file main.c which
contain [sic] something to help you test your function.


Examples: 
./picoshell /bin/ls "|" /usr/bin/grep picoshell
picoshell
./picoshell echo 'squalala' "|" cat "|" sed 's/a/b/g'
squblblb

___________________________________________________________________

Old summary by a student:
You are given a main function. It converts received arguments into cmds array
of strings. When there is a pipe the commands after the pipe are in the next
array of strings. You have to create a pipeline using the cmds you receive from
the main, and execute them. If there is any error the function should return 1.
Close all FFS before returning. If the cmds executed successfully wait all
child processes and return 0.
*/

#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int countCmds(char **cmds[]) {
	if (!cmds)
		return (-1);
	int i = 0;
	while (cmds[i])
		i++;
	return (i > 0 ? i : -1);
}

int    picoshell(char **cmds[]) {
	int N = countCmds(cmds);
	if (N == -1)
		return (1);
	int in_fd = STDIN_FILENO;
	for (int i = 0; i < N; i++) {
		int fd[2];
		if (i < N -1) {
			if (pipe(fd) == -1) {
				if (in_fd != STDIN_FILENO)
					close(in_fd);
				while (wait(NULL) != -1)
					;
				return (1);
			}
		}
		pid_t pid = fork();
		if (pid < 0) {
			close(fd[0]);
			close(fd[1]);
			if (in_fd != STDIN_FILENO)
				close(in_fd);
			while (wait(NULL) != -1)
				;
			return (1);
		}
		if (!pid) {
			if (in_fd != STDIN_FILENO) {
				dup2(in_fd, STDIN_FILENO);
				close(in_fd);
			}
			if (i < N - 1)
				dup2(fd[1], STDOUT_FILENO);
			close(fd[0]);
			close(fd[1]);
			execvp(cmds[i][0], cmds[i]);
			exit(1);
		}
		close(fd[1]);
		if (in_fd != STDIN_FILENO)
			close(in_fd);
		in_fd = fd[0];
	}
	while (wait(NULL) != -1)
		;
	return (0);
}

#include <stdio.h>
int main() {
	char *av1[] = {"ls", NULL};
	char *av2[] = {"cat", "-e", NULL};
	if (!picoshell((char **[]){av1, av2, av2, av2, av2, av2, av2, av2, av2, av2, av2, av2, av2, av2, av2, av2, av2, NULL}))
		printf("returned 0\n");
	else
		printf("returned 1\n");
	return (0);
}