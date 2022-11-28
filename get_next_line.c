/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falves-b <falves-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 11:36:32 by falves-b          #+#    #+#             */
/*   Updated: 2022/11/28 15:52:12 by falves-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	unsigned int	i;
	int				strlen;

	strlen = 0;
	while (src[strlen] != '\0')
		strlen++;
	i = 0;
	if (size == 0)
		return (strlen);
	while (i < size - 1 && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (strlen);
}

char	*ft_strdup(const char *s)
{
	int		size;
	char	*mem;

	size = ft_strlen(s) + 1;
	mem = malloc(size);
	if (!mem)
		return (NULL);
	ft_strlcpy(mem, s, size);
	return (mem);
}

static char	*ft_strchrnul(const char *s, int c)
{
	char	*ptr;

	ptr = strchr(s, c);
	if (!ptr)
		ptr = strchr(s, '\0');
	return (ptr);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*join;
	int		len1;
	int		len2;
	int		i;

	if (!s1)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	join = malloc(len1 + len2 + 1);
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
	return (join);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	i;

	if (!dst && !size)
		return (0);
	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	i = 0;
	if (size < dst_len + 1)
		return (size + src_len);
	if (size > dst_len + 1)
	{
		while (src[i] != '\0' && dst_len + 1 + i < size)
		{
			dst[dst_len + i] = src[i];
			i++;
		}
	}
	dst[dst_len + i] = '\0';
	return (dst_len + src_len);
}

char	*get_next_line(int fd)
{
	char		*chunk;
	static char	*line;
	char		*dup;
	char		*sep;
	int			read_bytes;

	
	if (!line)
		line = calloc(1, 1000);
	//printf("%s\n", line);
	while (1)
	{
		chunk = calloc(1, BUFFER_SIZE);
		read_bytes = read(fd, chunk, BUFFER_SIZE);
		if (!read_bytes)
			break ;
		sep = ft_strchrnul(chunk, '\n');
		ft_strlcat(line, chunk, ft_strlen(line) + sep - chunk + 1);
		if (chunk - sep < BUFFER_SIZE)
			break ;
	}
	sep = ft_strchrnul(line, '\n');
	dup = ft_strdup(line);
	ft_strlcpy(line, sep + 1, ft_strlen(sep) + 1);
	return (dup);
}

int main()
{
	char	*filePath1 = "teste";
	char	*line;
	int		fd1;
	int		i;

	
	i = 0;
	fd1 = open(filePath1, O_RDONLY);
	while (i < 10)
	{
		line = get_next_line(fd1);
		printf("%s\n", line);
		free(line);
		i++;
	}
	close(fd1);
	return (0);
}