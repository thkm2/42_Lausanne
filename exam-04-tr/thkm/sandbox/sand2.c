/*
Assignment name		:	sandbox
Expected files		:	sandbox.c
Allowed functions	:	fork, waitpid, exit, alarm, sigaction, kill, printf, strsignal, 
						errno, sigaddset, sigemptyset, sigfillset, sigdelset, sigismember
===============================================================================

Write the following function:

#include <stdbool.h>
int	sandbox(void (*f)(void), unsigned int timeout, bool verbose)

This function must test if the function f is a nice function or a bad function,
you will return 1 if f is nice , 0 if f is bad or -1 in case of an error in
your function.

A function is considered bad if it is terminated or stopped by a signal
(segfault, abort...), if it exit with any other exit code than 0 or if it
times out.

If verbose is true, you must write the appropriate message among the following:

"Nice function!\n"
"Bad function: exited with code <exit_code>\n"
"Bad function: <signal description>\n"
"Bad function: timed out after <timeout> seconds\n"

You must not leak processes (even in zombie state, this will be checked using
wait).

We will test your code with very bad functions.
*/

#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/errno.h>
#include <stdio.h>
#include <string.h>

void doNothing(int sig) {
	(void)sig;
}

int	sandbox(void (*f)(void), unsigned int timeout, bool verbose) {
	pid_t pid = fork();
	if (pid < 0)
		return (-1);
	if (!pid) {
		alarm(timeout);
		f();
		exit(0);
	}
	struct sigaction sa;
	sa.sa_handler = doNothing;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGALRM, &sa, NULL);
	alarm(timeout);
	int st;
	if (waitpid(pid, &st, 0) == -1) {
		if (errno == EINTR) {
			kill(pid, SIGKILL);
			waitpid(pid, NULL, 0);
			if (verbose)
				printf("Bad function: timed out after %d seconds\n", timeout);
			return (0);
		}
		return (-1);
	}
	alarm(0);
	if (WIFEXITED(st)) {
		int ex = WEXITSTATUS(st);
		if (ex == 0) {
			if (verbose)
				printf("Nice function!\n");
			return (1);
		}
		if (verbose)
			printf("Bad function: exited with code %d\n", ex);
		return (0);
	}
	if (WIFSIGNALED(st)) {
		if (WTERMSIG(st) == SIGALRM) {
			if (verbose)
				printf("Bad function: timed out after %d seconds\n", timeout);
			return (0);
		}
		if (verbose)
			printf("Bad function: %s\n", strsignal(WTERMSIG(st)));
		return (0);
	}
	return (-1);
}

void testF() {
	int *p = NULL;
	*p = 2;
}

int main() {
	sandbox(testF, 3, 1);
	return (0);
}