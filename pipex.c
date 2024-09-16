/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imraoui <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 14:28:33 by imraoui           #+#    #+#             */
/*   Updated: 2022/12/20 15:58:23 by imraoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_pipex(t_pipe *pipex)
{
	pipex->fd_infile = -1;
	pipex->fd_infile = -1;
	pipex->pid1 = -1;
	pipex->pid2 = -1;
}

char	**ft_get_path(char **envp)
{
	char	**paths;
	int		i;

	i = 0;
	while (!ft_strnstr(envp[i], "PATH", 4))
		i++;
	paths = ft_split(envp[i] + 5, ':');
	return (paths);
}

char	*get_cmd(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	char	*slash;
	int		i;

	i = 0;
	if (access(cmd, F_OK | X_OK) == 0)
		return (cmd);
	paths = ft_get_path(envp);
	i = -1;
	while (paths[++i])
	{
		slash = ft_strjoin(paths[i], "/");
		path = ft_strjoin(slash, cmd);
		free(slash);
		if (!access(path, F_OK | X_OK))
		{
			ft_free(paths);
			return (path);
		}
		free(path);
	}
	ft_free(paths);
	return (0);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipe	pipex;

	if (argc != 5)
		return (msg(ERR_INPUT));
	if (pipe(pipex.pfd) < 0)
		msg_error(ERR_PIPE);
	init_pipex(&pipex);
	child1(&pipex, argv, envp);
	child2(&pipex, argv, envp);
	ft_close(&pipex);
	waitpid(pipex.pid1, NULL, 0);
	waitpid(pipex.pid2, NULL, 0);
	return (0);
}
