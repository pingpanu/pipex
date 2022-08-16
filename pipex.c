/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pingpanu <pingpanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 16:48:39 by pingpanu          #+#    #+#             */
/*   Updated: 2022/08/16 16:34:11 by pingpanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	child_one_proc(t_cmd in, int *end, char **envp)
{
	dup2(in.fd, STDIN_FILENO);
	dup2(end[1], STDOUT_FILENO);
	close(end[0]);
	close(end[1]);
	if(execve(in.cmd_path, in.split_cmd, envp) == -1)
		error_exit("Command not found", 1);
}

static void	child_two_proc(t_cmd out, int *end, char **envp)
{
	dup2(end[0], STDIN_FILENO);
	dup2(out.fd, STDOUT_FILENO);
	close(end[0]);
	close(end[1]);
	if (execve(out.cmd_path, out.split_cmd, envp) == -1)
		error_exit("Command not found", 1);
}

void	pipex(t_cmd in, t_cmd out, char **envp)
{
	int	end[2];
	int	status;
	int	pid1;
	int	pid2;

	if (pipe(end) == -1)
		error_exit("Pipe", 1);
	pid1 = fork();
	if (pid1 < 0)
		error_exit("Fork", 1);
	if (pid1 == 0)
		child_one_proc(in, end, envp);
	pid2 = fork();
	if (pid2 < 0)
		error_exit("Fork", 1);
	if (pid2 == 0)
		child_two_proc(out, end, envp);
	close(end[0]);
	close(end[1]);
	waitpid(pid1, &status, 0);
	waitpid(pid2, &status, 0);
}
