/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falves-b <falves-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 15:29:10 by falves-b          #+#    #+#             */
/*   Updated: 2022/12/07 15:40:43 by falves-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*join;
	int		len1;
	int		len2;
	int		i;

	if (!s1)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	join = ft_calloc(1, len1 + len2 + 1);
	i = 0;
	if (join == NULL)
		return (NULL);
	while (i < len1)
	{
		join[i] = s1[i];
		i++;
	}
	while (i < len1 + len2)
	{
		join[i] = s2[i - len1];
		i++;
	}
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

char	*get_line(char *line, int fd)
{
	char	*buffer;
	int		bytes_read;

	buffer = ft_calloc(1, BUFFER_SIZE + 1);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (!line && bytes_read > 0)
		line = ft_calloc(1, 1);
	else if (bytes_read <= 0 && (!line || (ft_strchrnul(line, '\0') - ft_strchrnul(line, '\n')) <= 1))
	{
		free(line);
		free(buffer);
		return (NULL);
	}
	else if (strchr(line, '\n'))
		ft_memmove(line, strchr(line, '\n') + 1, ft_strchrnul(line, '\0') - (ft_strchrnul(line, '\n')));
	while (bytes_read > 0)
	{
		line = ft_strjoin(line, buffer);
		if (strchr(buffer, '\n'))
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
	char		*dup;

	if (fd < 0 || fd > FOPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	line[fd] = get_line(line[fd], fd);
	if (!line[fd])
		return (NULL);
	dup = ft_strndup(line[fd], ft_strchrnul(line[fd], '\n') - line[fd] + 1);
	return (dup);
}

/* int main()
{
	char	*filePath1 = "teste";
	char	*line;
	int		fd1;
	int		i;

	i = 0;
	fd1 = open(filePath1, O_RDONLY);
	while (i < 4)
	{
		line = get_next_line(fd1);
		printf("line %i = %s\n", i, line);
		free(line);
		i++;
	}
	close(fd1);
	return (0);
} */