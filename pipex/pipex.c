/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiraud <kgiraud@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:36:46 by kgiraud           #+#    #+#             */
/*   Updated: 2024/11/12 18:56:15 by kgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_process(char **av, char **envp, int *fd)
{
	int	filein;

	filein = open(av[1], O_RDONLY);
	if (filein == -1)
		error_exit();
	close(fd[0]);
	dup2(filein, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	exec(av[2], envp);
}

void	parent_process(char **av, char **envp, int *fd)
{
	int	fileout;

	fileout = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fileout == -1)
		error_exit();
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	dup2(fileout, STDOUT_FILENO);
	exec(av[3], envp);
}

int	main(int ac, char **av, char **envp)
{
	int		fd[2];
	pid_t	pid;

	if (ac != 5)
	{
		write(2, "Erreur...\n", 10);
		write(2, "Essaye dans ce format : './pipex file1 cmd1 cmd2 file2'\n",
			56);
		return (1);
	}
	if (pipe(fd) == -1)
		error_exit();
	pid = fork();
	if (pid == -1)
		error_exit();
	if (pid == 0)
		child_process(av, envp, fd);
	wait(NULL);
	parent_process(av, envp, fd);
}
