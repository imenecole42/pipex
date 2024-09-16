/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_pipe_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imraoui <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 18:16:07 by imraoui           #+#    #+#             */
/*   Updated: 2022/12/20 14:19:32 by imraoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	free_pfd(t_pipe *pipex)
{
	int	i;

	i = 0;
	while (i < pipex -> nbr_pipe)
	{
		free(pipex -> pfd[i]);
		i++;
	}
	free(pipex -> pfd);
}

int	reverse_pipes(t_pipe *pipex, int n)
{
	int	i;

	i = -1;
	if (pipex -> pfd)
	{
		while (pipex -> pfd[++i] && i < n)
			free_pfd(pipex);
		free_pfd(pipex);
	}
	return (0);
}

void	creat_pipes(t_pipe *pipex)
{
	int	i;

	i = -1;
	pipex->pfd = (int **)malloc(sizeof(int *) * (pipex->nbr_pipe + 1));
	if (!pipex->pfd)
		msg_error(ERR_PIPE);
	while (++i < pipex->nbr_pipe)
	{
		pipex->pfd[i] = (int *)malloc(sizeof(int) * (2));
		if ((!pipex->pfd[i]) || pipe(pipex->pfd[i]))
		{
			reverse_pipes(pipex, i);
			msg_error(ERR_PIPE);
		}
	}
	pipex->pfd[pipex->nbr_pipe] = 0;
}
