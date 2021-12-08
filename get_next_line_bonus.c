/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrechai <anrechai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 22:58:14 by anrechai          #+#    #+#             */
/*   Updated: 2021/12/08 00:14:22 by anrechai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (NULL);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

static char	*ft_found_line(char **dest, int fd)
{
	char		*buf;
	int			ret;

	buf = malloc(sizeof(char) * (BUFFER_SIZE) + 1);
	ret = 1;
	ret = read(fd, buf, BUFFER_SIZE);
	if (ret == -1)
	{
		free(buf);
		return (NULL);
	}
	while (ret > 0)
	{
		buf[ret] = '\0';
		dest[fd] = ft_strjoin(dest[fd], buf);
		if (ft_strchr(buf, '\n'))
			break ;
		ret = read(fd, buf, BUFFER_SIZE);
		buf[ret] = '\0';
	}
	free(buf);
	return (dest[fd]);
}

char	*get_next_line(int fd)
{
	static char	*dest[1024];
	char		*tmp;
	char		*line;
	int			i;

	if (fd < 0 || read(fd, NULL, 0) < 0)
		return (NULL);
	dest[fd] = ft_found_line(dest, fd);
	if (!dest[fd])
		return (NULL);
	if (!dest[fd][0])
	{
		free(dest[fd]);
		return (NULL);
	}
	i = 0;
	while (dest[fd][i] && dest[fd][i] != '\n')
		i++;
	if (dest[fd][i] == '\n')
		i++;
	line = ft_substr(dest[fd], 0, i);
	tmp = dest[fd];
	dest[fd] = ft_substr(tmp, i, ft_strlen(tmp) - 1);
	free(tmp);
	return (line);
}
