/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imraoui <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 14:01:42 by imraoui           #+#    #+#             */
/*   Updated: 2022/12/20 14:22:31 by imraoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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
		if (!access(path, F_OK))
		{
			ft_free(paths);
			return (path);
		}
		free(path);
	}
	ft_free(paths);
	return (0);
}

void	child(t_pipe *pipex, char **argv, char **envp)
{
	pipex->cmd = ft_split(argv[2 + pipex->here_doc + pipex->i], ' ');
	if (pipex->cmd[0] && get_cmd(pipex->cmd[0], envp))
	{
		execve(get_cmd(pipex->cmd[0], envp), pipex->cmd, envp);
		ft_free(pipex->cmd);
		free(pipex->pid);
		free_pfd(pipex);
		exit(127);
	}
	else
	{
		ft_putstr_fd(pipex->cmd[0], 2);
		write(2, ": command not found\n", 20);
		ft_free(pipex->cmd);
		free(pipex->pid);
		free_pfd(pipex);
		close(0);
		close(1);
		exit(127);
	}		
}

void	int_pipex(t_pipe *pipex, int argc, char **argv)
{
	pipex->nbr_cmd = argc - 3 - pipex->here_doc;
	pipex->nbr_pipe = 2 * (pipex->nbr_cmd - 1);
	open_infile(argv, pipex);
	open_outfile(argv[argc - 1], pipex);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipe	pipex;

	if (argc < is_pipex(argv[1], &pipex))
		return (msg(ERR_INPUT));
	else
	{
		int_pipex(&pipex, argc, argv);
		pipex.pid = (int *)malloc(sizeof(int) * (pipex.nbr_cmd));
		if (!pipex.pid)
			msg_error(ERR_PIPE);
		creat_pipes(&pipex);
		pipex.i = -1;
		while (++(pipex.i) < pipex.nbr_cmd)
			fork_pipe(&pipex, argv, envp);
		pipex.i = 0;
		while (pipex.i < pipex.nbr_cmd)
		{
			ft_close(&pipex);
			waitpid(pipex.pid[pipex.i], NULL, 0);
			pipex.i++;
		}
	}
	return (free(pipex.pid), free_pfd(&pipex), unlink(".heredok_tmp"));
}
