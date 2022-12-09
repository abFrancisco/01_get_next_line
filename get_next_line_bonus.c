/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falves-b <falves-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 15:29:10 by falves-b          #+#    #+#             */
/*   Updated: 2022/12/09 16:06:33 by falves-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*join;
	int		len1;
	int		len2;
	int		i;
	int		j;

	if (!s1)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	join = ft_calloc(1, len1 + len2 + 1);
	i = 0;
	j = 0;
	if (join == NULL)
		return (NULL);
	while (i < len1)
		join[i++] = s1[j++];
	while (i < len1 + len2)
		join[i++] = s2[j++ - len1];
	join[i] = '\0';
	free(s1);
	return (join);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*tmp_dest;
	char	*tmp_src;

	tmp_dest = (char *)dest;
	tmp_src = (char *)src;
	if (dest == src || n == 0)
		return (dest);
	if (dest < src)
		while (n--)
			*tmp_dest++ = *tmp_src++;
	else
		while (n--)
			tmp_dest[n] = tmp_src[n];
	return (dest);
}

int	nl_to_end(char *line)
{
	return ((ft_strchrnul(line, '\0') - ft_strchrnul(line, '\n')));
}

char	*get_line(char *line, int fd, int bytes_read)
{
	char	*buffer;

	buffer = ft_calloc(1, BUFFER_SIZE + 1);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (!line && bytes_read > 0)
		line = ft_calloc(1, 1);
	else if (bytes_read <= 0 && (!line || nl_to_end(line) <= 1))
	{
		free(line);
		free(buffer);
		return (NULL);
	}
	else if (ft_strchr(line, '\n'))
		ft_memmove(line, ft_strchr(line, '\n') + 1, nl_to_end(line));
	while (bytes_read > 0)
	{
		line = ft_strjoin(line, buffer);
		if (ft_strchr(buffer, '\n'))
			break ;
		free(buffer);
		buffer = calloc(1, BUFFER_SIZE + 1);
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	free(buffer);
	return (line);
}

char	*get_next_line(int fd)
{	
	static char	*line[FOPEN_MAX];
	char		*clean;

	if (fd < 0 || fd > FOPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	line[fd] = get_line(line[fd], fd, 0);
	if (!line[fd])
		return (NULL);
	clean = ft_strndup(line[fd], ft_strchrnul(line[fd], '\n') - line[fd] + 1);
	return (clean);
}
