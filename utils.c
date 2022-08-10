/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 10:14:53 by user              #+#    #+#             */
/*   Updated: 2022/08/10 10:32:29 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* utils is the place where functions from pipex.c are stored, but it's not path
** of printf or libft
*/

#include "include/pipex.h"
#include "include/libft.h"

void    free_charr(char **arr)
{
    if (*arr == NULL)
        return ;
    while (*arr)
    {
        free(*arr);
        *arr++;
    }
    free(arr);
}

char    *get_cmdpath(char *cmd, char **envp)
{
    
}