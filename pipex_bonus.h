/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imraoui <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 16:10:21 by imraoui           #+#    #+#             */
/*   Updated: 2022/12/20 16:38:33 by imraoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include<stdio.h>
# include<unistd.h>
# include<sys/types.h>
# include<sys/wait.h>
# include<stdlib.h>
# include<fcntl.h>
# include <memory.h>
# include <errno.h>
# include "libs/get_next_line.h"
# include "libs/libft.h"

# define ERR_INFILE "Infile"
# define ERR_HERDOC "herdoc"
# define ERR_OUTFILE "Outfile"
# define ERR_INPUT "Invalid number of arguments.\n"
# define ERR_PIPE "Pipe Failed"
# define ERR_FORK "fork failed\n"

typedef struct s_pipe
{
	int		fd_infile;
	int		fd_outfile;
	pid_t	*pid;
	int		**pfd;
	char	**cmd;
	int		nbr_cmd;
	int		here_doc;
	int		i;
	int		nbr_pipe;
}	t_pipe;

void	msg_error(char *err);
void	msg_error1(char *err);
void	ft_free(char **str);
void	ft_close(t_pipe *pipex);
int		msg(char *err);

void	ft_unlink(t_pipe *pipex);
void	ft_her_doc(t_pipe *pipex, char *limiter);
void	open_infile(char **argv, t_pipe *pipex);
void	open_outfile(char *argv, t_pipe *pipex);
int		is_pipex(char *argv, t_pipe *pipex);

void	free_pfd(t_pipe *pipex);
int		reverse_pipes(t_pipe *pipex, int n);
void	creat_pipes(t_pipe *pipex);

void	ft_dup(int src, int dest);
void	close_fd(t_pipe *pipex);
void	child1(t_pipe *pipex);
void	child2(t_pipe *pipex);
void	fork_pipe(t_pipe *pipex, char **argv, char **envp);

char	**ft_get_path(char **envp);
char	*get_cmd(char *cmd, char **envp);
void	child(t_pipe *pipex, char **argv, char **envp);
#endif
