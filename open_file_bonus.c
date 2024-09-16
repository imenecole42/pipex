/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imraoui <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 11:33:55 by imraoui           #+#    #+#             */
/*   Updated: 2022/12/20 14:00:30 by imraoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_unlink(t_pipe *pipex)
{
	pipex->fd_infile = open(".heredoc_tmp", O_RDONLY);
	if (pipex->fd_infile < 0)
	{
		unlink(".heredoc_tmp");
		msg_error(ERR_HERDOC);
	}	
}

void	ft_her_doc(t_pipe *pipex, char *limiter)
{
	char	fd;
	char	*str;
	char	buff[BUFFER_SIZE + 1];
	int		tmp;

	str = ft_strjoin(limiter, "\n");
	tmp = 0;
	fd = open(".heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		msg_error(ERR_HERDOC);
	while (1)
	{
		write(1, "heredoc> ", 9);
		tmp = read(0, buff, BUFFER_SIZE);
		if (tmp < 0)
			return ;
		buff[tmp] = '\0';
		if (!ft_strncmp(str, buff, ft_strlen(str)) || !tmp)
			break ;
		ft_putstr_fd(buff, fd);
	}
	free(str);
	close(fd);
	ft_unlink(pipex);
}

void	open_infile(char **argv, t_pipe *pipex)
{
	if (!ft_strncmp("here_doc", argv[1], 9))
		ft_her_doc(pipex, argv[2]);
	else
	{
		pipex->fd_infile = open(argv[1], O_RDONLY);
		if (pipex->fd_infile == -1)
			msg_error1(ERR_INFILE);
	}
}

void	open_outfile(char *argv, t_pipe *pipex)
{
	if (pipex->here_doc)
		pipex->fd_outfile = open(argv, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		pipex->fd_outfile = open(argv, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (pipex->fd_outfile == -1)
		msg_error1(ERR_OUTFILE);
}

int	is_pipex(char *argv, t_pipe *pipex)
{
	if (argv && !ft_strncmp("here_doc", argv, 9))
	{
		pipex->here_doc = 1;
		return (6);
	}
	else
	{
		pipex->here_doc = 0;
		return (5);
	}
}
