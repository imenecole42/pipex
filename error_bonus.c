/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imraoui <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 11:19:23 by imraoui           #+#    #+#             */
/*   Updated: 2022/12/20 11:20:51 by imraoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	msg_error(char *err)
{
	perror(err);
	exit (1);
}

void	msg_error1(char *err)
{
	perror(err);
}

int	msg(char *err)
{
	write(2, err, ft_strlen(err));
	return (1);
}

void	ft_free(char **str)
{
	int	n;
	int	i;

	i = 0;
	n = 0;
	while (str[n])
		n++;
	while (i < n)
		free(str[i++]);
	free(str);
}

void	ft_close(t_pipe *pipex)
{
	int	i;

	i = -1;
	while ((pipex->pfd[++i]))
	{
		if (pipex->pfd[i][0] > 2)
			close(pipex->pfd[i][0]);
		if (pipex->pfd[i][1] > 2)
			close(pipex->pfd[i][1]);
	}
	if (pipex->fd_infile > 2)
		close(pipex->fd_infile);
	if (pipex->fd_outfile > 2)
		close(pipex->fd_outfile);
}
