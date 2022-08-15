/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 16:48:39 by pingpanu          #+#    #+#             */
/*   Updated: 2022/08/15 21:14:15 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*note; this is the pseudocode to kick-start the project
{   
    int fd[2];

    if (pipe(fd) == -1)
        return 1;
    pid1 = fork();
    if (pid1 < 0)
        return 2;
    if (pid1 == 0)
    {
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
        close(fd[1]);
        execlp(argv[1], argv[2]);
    }
    pid2 = fork();
    if (pid2 < 0)
        return 3;
    if (pid2 == 0)
    {
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);
        close(fd[1]);
        execlp(argv[4], argv[3]);
    }
    close(fd[0]);
    close(fd[1]);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
    return (0);
}*/

static void	child_one_proc(t_cmd in, int *end, char **envp)
{
	dup2(in.fd, STDIN_FILENO);
	dup2(end[1], STDOUT_FILENO);
	close(end[0]);
	close(end[1]);
	execve(in.cmd_path, in.split_cmd, envp);
}

static void	child_two_proc(t_cmd out, int *end, char **envp)
{
	dup2(end[0], STDIN_FILENO);
	dup2(out.fd, STDOUT_FILENO);
	close(end[0]);
	close(end[1]);
	execve(out.cmd_path, out.split_cmd, envp);
}

void	pipex(t_cmd in, t_cmd out, char **envp)
{
	int	end[2];
	int	status;
	int	pid1;
	int	pid2;

	if (pipe(end) == -1)
		error_exit("Pipe's FD: ", 2);
	pid1 = fork();
	if (pid1 < 0)
		error_exit("Fork: ", -2);
	if (pid1 == 0)
		child_one_proc(in, end, envp);
	pid2 = fork();
	if (pid2 < 0)
		error_exit("Fork: ", -2);
	if (pid2 == 0)
		child_two_proc(out, end, envp);
	close(end[0]);
	close(end[1]);
	waitpid(pid1, &status, 0);
	waitpid(pid2, &status, 0);
}
