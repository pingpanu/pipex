/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 20:56:52 by user              #+#    #+#             */
/*   Updated: 2022/08/10 10:13:44 by user             ###   ########.fr       */
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

int main(int argc, char **argv, char **envp)
{
    int     fd1;
    int     fd2;

    if (argc != 5)
        return 1;
    fd1 = open(argv[1], O_RDONLY);
    fd2 = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
    if (fd1 < 0 || fd2 < 0)
        return (-1);
    pipex(fd1, fd2, argv, envp);
    return (0);
}