/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falves-b <falves-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 11:36:32 by falves-b          #+#    #+#             */
/*   Updated: 2022/11/22 15:23:17 by falves-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*buff;
	char		*buff_start;
	char		*match;
	int			eol;
	static int	i;

	buff = malloc(10000);
	match = (NULL);
	eol = 1;
	if (!i)
		i = 0;
	while (eol > 0)
	{
		eol = read(fd, buff[i], BUFFER_SIZE);
		match = memchr(buff[i], '\n', BUFFER_SIZE);
		if (match)
		{
			i = i + (match - buff[i] + 1);
			eol = 0;
		}
		else
			i = i + BUFFER_SIZE;
	}
	free(buff);
	return (buff[i]);
}

int main()
{
	char	*filePath1 = "teste";
	char	*line;
	int		fd1;
	int		i;

	i = 0;

	//filePath1 = argv[1];
	fd1 = open(filePath1, O_RDONLY);
	while (i < 5)
	{
		line = get_next_line(fd1);
		printf("%s", line);
		free(line);
		
		i++;
	}
	close(fd1);
	return (0);
}