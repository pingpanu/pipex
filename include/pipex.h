/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pingpanu <pingpanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 21:02:45 by user              #+#    #+#             */
/*   Updated: 2022/08/16 16:20:24 by pingpanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
/* include for all allowed function
** note: unistd.h and stdlib.h shall not be included as it already 
**       had been include in libft.h*/
# include "libft.h"
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>

/*this struct is for cmd parameters*/
typedef struct s_cmd
{
    int     fd;
    char    **split_cmd;
    char    *cmd_path;
}   t_cmd;

/*these are mandatory function*/
void	error_exit(char *message, int per);
void	pipex(t_cmd in, t_cmd out, char **envp);
void	free_charr(char **arr);
char	*get_cmdpath(char *cmd, char **envp);
#endif
