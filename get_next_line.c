/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falves-b <falves-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 11:36:32 by falves-b          #+#    #+#             */
/*   Updated: 2022/12/06 14:52:25 by falves-b         ###   ########.fr       */
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
	int		i;
	int		bytes_read;
	int		offset;

	i = 0;
	offset = 0;
	buffer = calloc(1, BUFFER_SIZE + 1);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (!bytes_read && (!line || (ft_strchrnul(line, '\0') - ft_strchrnul(line, '\n')) <= 1))
	{
		free(line);
		free(buffer);
		return (NULL);
	}
	else if (!line)
		line = calloc(1, 10000000);
	else if (strchr(line, '\n'))
	{
		ft_memmove(line, strchr(line, '\n') + 1, ft_strchrnul(line, '\0') - (strchr(line, '\n')));
		offset = ft_strlen(line);
		bzero(line + offset, BUFFER_SIZE - offset);
	}
	while (bytes_read)
	{
		ft_memmove((line + (i++ * BUFFER_SIZE)) + offset, buffer, BUFFER_SIZE);
		if (strchr(buffer, '\n'))
			break ;
		bzero(buffer, BUFFER_SIZE + 1);
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	line[(i*BUFFER_SIZE) + offset] = '\0';
	free(buffer);
	return (line);
}

char	*get_next_line(int fd)
{	
	static char	*line;
	char		*dup;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = get_line(line, fd);
	if (!line)
		return (NULL);
	dup = strndup(line, ft_strchrnul(line, '\n') - line + 1);
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
	while (i < 10)
	{
		line = get_next_line(fd1);
		printf("line %i = %s\n", i, line);
		free(line);
		i++;
	}
	close(fd1);
	return (0);
} */