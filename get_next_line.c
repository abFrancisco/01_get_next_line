/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falves-b <falves-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 11:36:32 by falves-b          #+#    #+#             */
/*   Updated: 2022/11/22 17:40:53 by falves-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
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
	static char	*buff;
	char		*buff_start;
	char		*match;
	int			eol;

	buff_start = calloc(1, 10000000);
	match = NULL;
	eol = 1;
	while (eol > 0)
	{
		buff = calloc(1, BUFFER_SIZE + 7);
		eol = read(fd, buff, BUFFER_SIZE);
		match = memchr(buff, '\n', BUFFER_SIZE);
		if (match)
			eol = 0;
		ft_strlcat(buff_start, buff, ft_strlen(buff_start) + BUFFER_SIZE + 1);
		free(buff);
	}
	return (buff_start);
}

/* int main()
{
	char	*filePath1 = "teste";
	char	*line;
	int		fd1;
	int		i;

	i = 0;
	fd1 = open(filePath1, O_RDONLY);
	while (i < 6)
	{
		line = get_next_line(fd1);
		printf("line %i = %s", i, line);
		free(line);
		i++;
	}
	close(fd1);
	return (0);
} */