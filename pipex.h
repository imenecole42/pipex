/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imraoui <imraoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 16:02:15 by imraoui           #+#    #+#             */
/*   Updated: 2022/12/20 16:09:46 by imraoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <fcntl.h>
# include <memory.h>
# include <errno.h>
# include "libs/get_next_line.h"
# include "libs/libft.h"

# define ERR_INFILE "Infile"
# define ERR_OUTFILE "Outfile"
# define ERR_INPUT "Invalid number of arguments.\n"
# define ERR_PIPE "Pipe Failed"
# define ERR_FORK "fork failed\n"

typedef struct s_pipe
{
	int		fd_infile;
	int		fd_outfile;
	pid_t	pid1;
	pid_t	pid2;
	int		pfd[2];
	char	**cmd;
}	t_pipe;

int		msg(char *err);
void	msg_error(char *err);
void	msg_error1(char *err);
char	**ft_get_path(char **envp);
char	*get_cmd(char *cmd, char **envp);
void	ft_free(char **str);
void	child1(t_pipe *pipex, char **argv, char **envp);
void	open_infile(t_pipe *pipex, char **argv);
void	dup_child1(t_pipe *pipex);
void	child2(t_pipe *pipex, char **argv, char **envp);
void	dup_child2(t_pipe *pipex);
void	open_outfile(t_pipe *pipex, char **argv);
void	ft_close(t_pipe *pipex);
void	msg_error1(char *err);
#endif
