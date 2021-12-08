/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrechai <anrechai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 16:49:53 by anrechai          #+#    #+#             */
/*   Updated: 2021/12/08 00:13:45 by anrechai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

static char	*ft_found_line(char *dest, int fd)
{
	char		*buf;
	int			ret;

	buf = malloc(sizeof(char) * (BUFFER_SIZE) + 1);
	ret = 1;
	ret = read(fd, buf, BUFFER_SIZE);
	while (ret > 0)
	{
		buf[ret] = '\0';
		dest = ft_strjoin(dest, buf);
		if (ft_strchr(buf, '\n'))
			break ;
		ret = read(fd, buf, BUFFER_SIZE);
		buf[ret] = '\0';
	}
	free(buf);
	return (dest);
}

char	*get_next_line(int fd)
{
	static char	*dest = NULL;
	char		*tmp;
	char		*line;
	int			i;

	if (fd < 0)
		return (NULL);
	dest = ft_found_line(dest, fd);
	if (!dest)
		return (NULL);
	if (!dest[0])
	{
		free(dest);
		return (NULL);
	}
	i = 0;
	while (dest[i] && dest[i] != '\n')
		i++;
	if (dest[i] == '\n')
		i++;
	line = ft_substr(dest, 0, i);
	tmp = dest;
	dest = ft_substr(tmp, i, ft_strlen(tmp) - 1);
	free(tmp);
	return (line);
}
