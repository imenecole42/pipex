/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imraoui <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 15:54:22 by imraoui           #+#    #+#             */
/*   Updated: 2022/12/20 15:55:56 by imraoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	open_infile(t_pipe *pipex, char **argv)
{
	pipex->fd_infile = open(argv[1], O_RDONLY);
	if (pipex->fd_infile == -1)
	{
		ft_close(pipex);
		msg_error(ERR_INFILE);
	}
	dup_child1(pipex);
}

void	open_outfile(t_pipe *pipex, char **argv)
{
	pipex->fd_outfile = open(argv[4], O_TRUNC | O_CREAT | O_RDWR, 0000644);
	if (pipex->fd_outfile < 0)
	{
		ft_close(pipex);
		msg_error(ERR_OUTFILE);
	}
	dup_child2(pipex);
}

void	dup_child1(t_pipe *pipex)
{
	close(pipex->pfd[0]);
	dup2(pipex->pfd[1], 1);
	close(pipex->pfd[1]);
	dup2(pipex->fd_infile, 0);
	close(pipex->fd_infile);
}

void	dup_child2(t_pipe *pipex)
{
	close(pipex->pfd[1]);
	dup2(pipex->pfd[0], 0);
	close(pipex->pfd[0]);
	dup2(pipex->fd_outfile, 1);
	close(pipex->fd_outfile);
}
