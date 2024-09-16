/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imraoui <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 15:49:13 by imraoui           #+#    #+#             */
/*   Updated: 2022/12/20 15:53:29 by imraoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child1(t_pipe *pipex, char *argv[], char *envp[])
{
	pipex->pid1 = fork();
	if (pipex->pid1 == -1)
	{	
		ft_close(pipex);
		msg_error(ERR_FORK);
	}
	if (pipex->pid1 == 0)
	{
		open_infile(pipex, argv);
		pipex->cmd = ft_split(argv[2], ' ');
		if (pipex->cmd[0] && get_cmd(pipex->cmd[0], envp))
		{
			execve(get_cmd(pipex->cmd[0], envp), pipex->cmd, envp);
			ft_free(pipex->cmd);
		}
		else
		{
			ft_putstr_fd(pipex->cmd[0], 2);
			write(2, ": command not found\n", 20);
			ft_free(pipex->cmd);
			close(0);
			exit(1);
		}			
	}
}
//pipe[0] -> read / pipe[1] -> write
// 0 : STDin, 1 : STDout

void	child2(t_pipe *pipex, char *argv[], char *envp[])
{
	pipex->pid2 = fork();
	if (pipex->pid2 == -1)
	{
		close(pipex->fd_infile);
		ft_close(pipex);
		msg_error(ERR_FORK);
	}
	if (pipex->pid2 == 0)
	{
		open_outfile(pipex, argv);
		pipex->cmd = ft_split(argv[3], ' ');
		if (pipex->cmd[0] && get_cmd(pipex->cmd[0], envp))
		{
			execve(get_cmd(pipex->cmd[0], envp), pipex->cmd, envp);
			ft_free(pipex->cmd);
		}
		else
		{
			ft_putstr_fd(pipex->cmd[0], 2);
			write(2, ": command not found\n", 20);
			ft_free(pipex->cmd);
			close(1);
			exit(1);
		}
	}
}
