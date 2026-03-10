/* Allowed functions: pipe, fork, dup2, execvp, close, exit

write the following function:
	
	int	ft_popen(const char *file, char *const argv[], char type)

The function must launch the executable file with the arguments argv (using execvp).
If the type is 'r' the function must return a file descriptor connected to the output of the command.
If the type is 'w' the function must return a file descriptor connected to the input of the command.
In case of error or invalid parameter the function must return -1.

Hint: Do not leak file descriptors! */

#include <unistd.h>
#include <stdlib.h>

int	ft_popen(const char *file, char *const argv[], char type) {
	if (!file || !argv || (type != 'r' && type != 'w'))
		return (-1);
	int fd[2];
	if (pipe(fd) == -1)
		return (-1);
	int parent, child, std;
	if (type == 'r') {
		parent = 0;
		child = 1;
		std = STDOUT_FILENO;
	}
	else if (type == 'w') {
		parent = 1;
		child = 0;
		std = STDIN_FILENO;
	}
	pid_t pid = fork();
	if (pid < 0) {
		close(fd[0]);
		close(fd[1]);
		write(1, "1\n", 1);
		return (-1);
	}
	if (!pid) {
		close(fd[parent]);
		dup2(fd[child], std);
		close(fd[child]);
		execvp(file, argv);
		exit(1);
	}
	close(fd[child]);
	return (fd[parent]);
}

#include <stdio.h>
int main() {
	int fd = ft_popen("ls", (char *const[]){"ls", "-C", NULL}, 'r');
	char buf[1];
	while (read(fd, buf, 1))
		write(1, buf, 1);
	close(fd);

	int fd2 = ft_popen("cat", (char *const[]){"cat", NULL}, 'w');
	printf("fd2 : %d\n", fd2);
	dprintf(fd2, "je suis le test 2\n");
	close(fd2);
	return (0);
}