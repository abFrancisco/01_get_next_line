/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falves-b <falves-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 11:36:32 by falves-b          #+#    #+#             */
/*   Updated: 2022/11/30 16:14:30 by falves-b         ###   ########.fr       */
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

char	*get_next_line(int fd)
{
	char		*chunk;
	static char	*line;
	char		*dup;
	char		*sep;
	int			flag;

	dup = calloc(500,1);
	flag = 1;
	//printf("line a = %s\n", line);
	if (!line)
		line = calloc(1, 1000);
	//printf("line b = %s\n", line);
	if (strchr(line, '\n'))
		sep = ft_strchrnul(line, '\n');
	else
	{
		while (flag)
		{
			chunk = calloc(1, BUFFER_SIZE);
			flag = read(fd, chunk, BUFFER_SIZE);
			sep = ft_strchrnul(chunk, '\n');
			ft_strlcat(line, chunk, ft_strlen(line) + BUFFER_SIZE);
			if (sep - chunk < BUFFER_SIZE)
				flag = 0;
		}
	}
	//dup = strndup(line, sep - line + 1);
	ft_strlcpy(dup, line, sep - line);//causes segmentation fault because dup doesnt have enough space
	ft_memmove(line, sep + 1, sep - line);
	//printf("line c = %s\n", line);
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
		printf("line %i = %s", i, line);
		i++;
	}
	free(line);
	close(fd1);
	return (0);
}

/*
#include "get_next_line.h"

char	*ft_readed_line(char *start)
{
	int		i;
	char	*line;

	if (!start || !start[0])
		return (NULL);
	i = 0;
	while (start[i] && start[i] != '\n')
		i++;
	if (start[i] == '\n')
		i++;
	line = (char *)malloc(1 + i * sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (start[i] && start[i] != '\n')
	{
		line[i] = start[i];
		i++;
	}
	if (start[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*ft_move_start(char	*start)
{
	char	*new_buff;
	int		i;
	int		j;

	i = 0;
	while (start[i] && start[i] != '\n')
		i++;
	if (start[i] == '\0')
	{
		free(start);
		return (NULL);
	}
	i += (start[i] == '\n');
	new_buff = (char *)malloc(1 + ft_strlen(start) - i);
	if (!new_buff)
		return (NULL);
	j = 0;
	while (start[i + j])
	{
		new_buff[j] = start[i + j];
		j++;
	}
	new_buff[j] = '\0';
	free(start);
	return (new_buff);
}

char	*get_next_line(int fd)
{
	char		*tmp;
	int			fd_read;
	static char	*start_str;

	if (fd < 0 || BUFFER_SIZE <= 0)printf("line a = %s", line);
		return (NULL);
	fd_read = 1;
	tmp = (char *)malloc(1 + BUFFER_SIZE * sizeof(char));
	if (!tmp)
		return (NULL);
	while (!(ft_strchr(start_str, '\n')) && fd_read != 0)
	{
		fd_read = read(fd, tmp, BUFFER_SIZE);
		if (fd_read == -1)
		{
			free(tmp);
			return (NULL);
		}
		tmp[fd_read] = '\0';
		start_str = ft_strjoin(start_str, tmp);
	}
	free(tmp);
	tmp = ft_readed_line(start_str);
	start_str = ft_move_start(start_str);
	return (tmp);
}
*/