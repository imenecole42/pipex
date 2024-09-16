/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imraoui <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 11:11:17 by imraoui           #+#    #+#             */
/*   Updated: 2022/12/20 11:17:24 by imraoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_dup(int src, int dest)
{
	dup2(src, 1);
	dup2(dest, 0);
}

void	close_fd(t_pipe *pipex)
{
	ft_close(pipex);
	free_pfd(pipex);
	free(pipex->pid);
	exit(127);
}

void	child1(t_pipe *pipex)
{
	if (pipex -> fd_infile < 0)
		return (close_fd(pipex));
	ft_dup(pipex -> pfd[pipex->i][1], pipex->fd_infile);
	ft_close(pipex);
}

void	child2(t_pipe *pipex)
{
	if (pipex -> fd_outfile < 0)
		return (close_fd(pipex));
	ft_dup(pipex->fd_outfile,
		pipex->pfd[pipex->i - 1][0]);
	ft_close(pipex);
}

void	fork_pipe(t_pipe *pipex, char **argv, char **envp)
{
	pipex -> pid[pipex -> i] = fork();
	if (pipex -> pid[pipex -> i] == -1)
		return (write(2, "Error Fork\n", 12), free(NULL));
	if (pipex -> pid[pipex -> i] == 0)
	{
		if (pipex ->i == 0)
			child1(pipex);
		else if (pipex -> i == pipex->nbr_cmd - 1)
			child2(pipex);
		else
		{
			ft_dup(pipex -> pfd[pipex -> i][1],
				pipex -> pfd[pipex -> i - 1][0]);
			ft_close(pipex);
		}
		child(pipex, argv, envp);
	}
}
