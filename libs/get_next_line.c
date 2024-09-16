/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imraoui <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 15:00:17 by imraoui           #+#    #+#             */
/*   Updated: 2022/06/14 19:57:24 by imraoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_select(char *str)
{
	char	*dest;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str && str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		dest = (char *) malloc(sizeof(char) * (i + 2));
	else if (str[i] == '\0')
		dest = (char *) malloc(sizeof(char) *(i + 1));
	if (!dest)
		return (NULL);
	while (str[j] && str[j] != '\n')
	{
		dest[j] = str[j];
		j++;
	}
	if (str[j] == '\n')
		dest[j++] = '\n';
	dest[j] = '\0';
	return (dest);
}

char	*ft_select2(char *str)
{
	char	*dest;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
		return (NULL);
	if (str[i] == '\n')
		dest = (char *)malloc(sizeof(char) * (ft_strlen1(str) - i + 1));
	if (!dest)
		return (NULL);
	i++;
	while (str && str[i])
	{
		dest[j] = str[i];
		i++;
		j++;
	}
	dest[j] = '\0';
	return (dest);
}

char	*get_read_line(int fd, char *str)
{
	static char	buff[BUFFER_SIZE + 1];
	char		*temp;
	int			res;

	res = 1;
	while (res > 0 && (!str || !ft_strchr1(str, '\n')))
	{
		res = read(fd, buff, BUFFER_SIZE);
		if (res == -1)
			return (NULL);
		buff[res] = '\0';
		temp = str;
		str = ft_strjoin1(temp, buff);
	}
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*str = NULL;
	char		*temp;
	char		*ligne;

	if (fd < 0 || fd > 1023 || BUFFER_SIZE <= 0)
		return (NULL);
	str = get_read_line(fd, str);
	if (!str)
		return (NULL);
	if (!str[0])
	{
		free(str);
		str = NULL;
		return (NULL);
	}
	ligne = ft_select(str);
	temp = ft_select2(str);
	if (str != NULL)
		free(str);
	str = temp;
	return (ligne);
}
/*
int main()
{
	int fd;
	fd = open("coucou",O_RDONLY);
	char *ligne;
	ligne = NULL;
	while(1)
	{
		ligne = get_next_line(fd);
		if (!ligne)
			break ;
		if (ligne != NULL)
			printf("%s",ligne);
		free(ligne);
	}
	return (0);
}
*/
/*
void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
void	ft_putstr_fd(char *s, int fd)
{
	unsigned int	i;

	i = 0;
	while (s[i] != '\0')
	{
		write(fd, &s[i], 1);
		i++;
    }
}
void	ft_putendl_fd(char *s, int fd)
{
	ft_putstr_fd(s, fd);
	ft_putchar_fd('\n', fd);
}

int			main(int ac, char **av)
{
	int		fd;
	char	*line;

	line = NULL;
	fd = open(av[ac-1], O_RDONLY);
	while (get_next_line(fd))
	{
		ft_putendl_fd(line,fd);
	}
	close(fd);
}
*/
