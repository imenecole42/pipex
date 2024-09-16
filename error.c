/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imraoui <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 11:21:42 by imraoui           #+#    #+#             */
/*   Updated: 2022/12/20 11:33:04 by imraoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	msg(char *err)
{
	write(2, err, ft_strlen(err));
	return (1);
}

void	msg_error(char *err)
{
	perror(err);
	exit (1);
}

void	msg_error1(char *err)
{
	perror(err);
	exit (1);
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
	if (pipex->pfd[0] > 2)
		close(pipex->pfd[0]);
	if (pipex->pfd[1] > 2)
		close(pipex->pfd[1]);
}
