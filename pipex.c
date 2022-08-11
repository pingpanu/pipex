/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pingpanu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 16:48:39 by pingpanu          #+#    #+#             */
/*   Updated: 2022/08/11 15:35:06 by pingpanu         ###   ########.fr       */
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

static void	child_one_proc(int file1, int *end, char *cmd1, char **envp)
{
	char	*cmd1_path;
	char	**split_cmd1;

	dup2(file1, STDIN_FILENO);
	dup2(end[1], STDOUT_FILENO);
	close(end[0]);
	close(end[1]);
	split_cmd1 = ft_split(cmd1, ' ');
	if (!split_cmd1)
	{
		free_charr(split_cmd1);
		error_exit("Malloc :", 3);
	}
	cmd1_path = get_cmdpath(cmd1, envp);
	if (!cmd1_path)
	{
		free(cmd1_path);
		error_exit("Malloc :", 3);
	}
	execve(cmd1_path, split_cmd1, envp);
	free_charr(split_cmd1);
	free(cmd1_path);
}

static void	child_two_proc(int file2, int *end, char *cmd2, char **envp)
{
	char	*cmd2_path;
	char	**split_cmd2;

	dup2(end[0], STDIN_FILENO);
	dup2(file2, STDOUT_FILENO);
	close(end[0]);
	close(end[1]);
	split_cmd2 = ft_split(cmd2, ' ');
	if (!split_cmd2)
	{
		free_charr(split_cmd2);
		error_exit("Malloc :", 3);
	}
	cmd2_path = get_cmdpath(split_cmd2[0], envp);
	if (!cmd2_path)
	{
		free(cmd2_path);
		error_exit("Malloc :", 3);
	}
	execve(cmd2_path, split_cmd2, envp);
	free_charr(split_cmd2);
	free(cmd2_path);
}

void	pipex(int file1, int file2, char **argv, char **envp)
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
		child_one_proc(file1, end, argv[2], envp);
	pid2 = fork();
	if (pid2 < 0)
		error_exit("Fork: ", -2);
	if (pid2 == 0)
		child_two_proc(file2, end, argv[3], envp);
	close(end[0]);
	close(end[1]);
	waitpid(pid1, &status, 0);
	waitpid(pid2, &status, 0);
}
