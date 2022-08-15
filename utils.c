/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 16:49:03 by pingpanu          #+#    #+#             */
/*   Updated: 2022/08/14 23:54:48 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* utils is the place where functions from pipex.c are stored, but it's not path
** of printf or libft
*/

#include "pipex.h"
#include "libft.h"

static char	*check_access(char **path_arr, char *cmd)
{
	char	*proto_ret;
	char	*ret;
	int		i;

	i = 0;
	while (path_arr[i])
	{
		proto_ret = ft_strjoin(path_arr[i], "/");
		ret = ft_strjoin(proto_ret, cmd);
		free(proto_ret);
		if (access(ret, F_OK) == 0)
			return (ret);
		free(ret);
		i++;
	}
	return (NULL);
}

void	free_charr(char **arr)
{
	int	i;

	i = -1;
	if (arr == NULL)
		return ;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}

char	*get_cmdpath(char *cmd, char **envp)
{
	char	*path;
	char	**path_arr;
	int		i;

	i = 0;
	while (ft_strncmp(envp[i], "PATH", 4) != 0)
		i++;
	path_arr = ft_split(envp[i] + 5, ':');
	if (!path_arr)
	{
		free_charr(path_arr);
		return (NULL);
	}
	path = check_access(path_arr, cmd);
	free_charr(path_arr);
	return (path);
}

/*for test only
int	main(int argc, char **argv, char **envp)
{
	char	*which;
	char	**cmd;

	if (argc < 2)
		return (1);
	cmd = ft_split(argv[1], ' ');
	int	i = 0;
	while (cmd[i])
	{
		printf("%d %s\n",i, cmd[i]);
		i++;
	}
	which = get_cmdpath(cmd[0], envp);
	printf("%s\n", which);
	free(which);
	return (0);
}*/