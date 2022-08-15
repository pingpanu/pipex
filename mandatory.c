/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandatory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 16:49:17 by pingpanu          #+#    #+#             */
/*   Updated: 2022/08/15 21:18:48 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*---------------------------------------PIPEX----------------------------------
** PIPEX is a program to simulate pipe " | " in shell script, it work like this
** 1) Execute infile with cmd1 (STDIN "infile" --> cmd1)
** 2) Write cmd1 to end[1] (end[1] = cmd1 STDOUT)
** 3) Pipe end[1] to end[0] (end[1] --> end[0])
** 4) Execute cmd1 output with cmd2 (STDIN "cmd1" --> cmd2)
** 5) cmd2 write its output to outfile (STDOUT "cmd2" --> outfile)
** Note: Pipe (3) is two-way communication (like two-way switch)
** ------------------------------------To do list-------------------------------
** 1) Get no-of-argument (argc) arguments (argv) and environmental variable (env)
** 2) Check if argc == 5, for bonus it's argc >= 5
** 3) Get file descriptors for both child processes with open()
** 4) Check if all file descriptors >= 0
** 5) Pipe(end[2]) and check that its != -1 (mean error)
** 6) Fork pid for cmd1, check if its == 0. 
** 7) If yes, dup2(file1, STDIN_FILENO) and dup2(end[1], STDOUT_FILENO)
** 8) Close both ends of the pipe
** 9) Find path of cmd1 (replicate which cmd1 in terminal)
** 10) Put cmd1_path, cmd1, and envp to execve(...) command
** 11) Repeat 6 to 9 but now it's cmd2.
** 12) cmd2 differ from cmd1, its dup2(end[0], STDIN_FILENO) and dup2(file2, STDOUT_FILENO)
** 13) Close both ends after two child process had ran
** 14) Use waitpid to observe status of both cmds, and it's finish now.
*/

void	error_exit(char *message, int ret)
{
	perror(message);
	exit(ret);
}

/*static void		check_strs(t_cmd *in, t_cmd *out)
{
	if (!in->split_cmd)
	{
		free_charr(in->split_cmd);
		error_exit("Cmd1 :", 3);
	}
	if (!in->cmd_path)
	{
		free(in->cmd_path);
		error_exit("Cmd1 path :", 3);
	}
	if (!out->split_cmd)
	{
		free_charr(out->split_cmd);
		error_exit("Cmd2 :", 3);
	}
	if (!out->cmd_path)
	{
		free(out->cmd_path);
		error_exit("Cmd2 path :", 3);
	}
}*/

static void		free_tcmd(t_cmd *in, t_cmd *out)
{
	free(in->cmd_path);
	free_charr(in->split_cmd);
	free(out->cmd_path);
	free_charr(out->split_cmd);
}

int	main(int argc, char **argv, char **envp)
{
	t_cmd	in;
	t_cmd	out;

	if (argc != 5)
		error_exit("Arguments: ", 1);
	in.fd = open(argv[1], O_RDONLY);
	if (in.fd < 0)
		error_exit("Infile FD :", -1);
	out.fd = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (out.fd < 0)
		error_exit("Outfile FD :", -1);
	in.split_cmd = ft_split(argv[2], ' ');
	in.cmd_path = get_cmdpath(in.split_cmd[0], envp);
	out.split_cmd = ft_split(argv[3], ' ');
	out.cmd_path = get_cmdpath(out.split_cmd[0], envp);
	/*the check_strs may not be neccessary function
	check_strs(&in, &out);*/
	pipex(in, out, envp);
	free_tcmd(&in, &out);
	return (0);
}