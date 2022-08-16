/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandatory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pingpanu <pingpanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 16:49:17 by pingpanu          #+#    #+#             */
/*   Updated: 2022/08/16 16:43:51 by pingpanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_exit(char *message, int per)
{
	if (per == 0)
		ft_putstr_fd(message, 2);
	else
		perror(message);
	exit(1);
}

static void	free_tcmd(t_cmd *in, t_cmd *out)
{
	free(in->cmd_path);
	free_charr(in->split_cmd);
	free(out->cmd_path);
	free_charr(out->split_cmd);
}

static int	check_cmds(char *cmd1, char *cmd2)
{
	int		i;

	i = -1;
	while (cmd1[++i])
	{
		if (!ft_isalpha(cmd1[i]))
			return (0);
	}
	i = -1;
	while (cmd2[++i])
	{
		if (!ft_isalpha(cmd2[i]))
			return (0);
	}
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_cmd	in;
	t_cmd	out;

	if (argc != 5)
		error_exit("Invalid number of arguments", 0);
	in.fd = open(argv[1], O_RDONLY);
	out.fd = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (in.fd < 0 || out.fd < 0)
		error_exit("No such file or directory\n", 0);
	in.split_cmd = ft_split(argv[2], ' ');
	in.cmd_path = get_cmdpath(in.split_cmd[0], envp);
	out.split_cmd = ft_split(argv[3], ' ');
	out.cmd_path = get_cmdpath(out.split_cmd[0], envp);
	if (!check_cmds(in.split_cmd[0], out.split_cmd[0]))
	{
		free_tcmd(&in, &out);
		error_exit("Command not found\n", 0);
	}
	pipex(in, out, envp);
	free_tcmd(&in, &out);
	return (0);
}