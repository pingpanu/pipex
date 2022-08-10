/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 21:02:45 by user              #+#    #+#             */
/*   Updated: 2022/08/10 10:30:11 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
/* include for all allowed function
** note: unistd.h and stdlib.h shall not be included as it already 
**       had been include in libft.h*/
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>

/*these are mandatory function*/
void    pipex(int file1, int file2, char **argv, char **envp);
#endif