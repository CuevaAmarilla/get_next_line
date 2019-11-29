/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alromero <alromero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 13:26:32 by alromero          #+#    #+#             */
/*   Updated: 2019/11/29 15:27:26 by alromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

static int	ft_line(char **aux, char **line)
{
	int		i;
	char	*other;

	i = 0;
	while ((*aux)[i] != '\n' && (*aux)[i] != '\0')
		i++;
	if ((*aux)[i] == '\n')
	{
		*line = ft_substr(*aux, 0, i);
		other = ft_substr(&(*aux)[i + 1], 0, ft_strlen(&(*aux)[i + 1]));
		free(*aux);
		*aux = other;
	}
	else
	{
		*line = *aux;
		*aux = NULL;
		return (0);
	}
	return (1);
}

static int	flag(int mp, char **line, char **aux)
{
	if (mp < 0)
		return (-1);
	else if (mp == 0 && *aux == NULL)
	{
		*line = ft_strdup("");
		return (0);
	}
	else
		return (ft_line(aux, line));
}

int			get_next_line(int fd, char **line)
{
	int			mp;
	char		*temp;
	static char	*aux[4096];
	char		buff[BUFFER_SIZE + 1];

	if (fd < 0 || line == NULL || BUFFER_SIZE <= 0)
		return (-1);
	while ((mp = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[mp] = '\0';
		if (aux[fd] == NULL)
			aux[fd] = ft_strdup(buff);
		else
		{
			temp = ft_strjoin(aux[fd], buff);
			free(aux[fd]);
			aux[fd] = temp;
		}
		if (ft_strchr(aux[fd], '\n'))
			break ;
	}
	return (flag(mp, line, &aux[fd]));
}
