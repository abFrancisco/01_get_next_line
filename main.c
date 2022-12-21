/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falves-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 12:27:40 by falves-b          #+#    #+#             */
/*   Updated: 2022/12/21 13:32:42 by falves-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

char	*ft_strjoin2(char *s1, char *s2)
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
	return (join);
}

static int	ft_nlen(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*str;
	long	l;
	int		len;

	len = ft_nlen(n);
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	l = n;
	if (n < 0)
	{
		l = -l;
		str[0] = '-';
	}
	while (l)
	{
		str[len - 1] = (l % 10) + '0';
		l = l / 10;
		len--;
	}
	if (n == 0)
		str[len - 1] = '0';
	return (str);
}

int main(void)
{
	int		fds[50];
	int		i;
	int		j;
	char	*path;
	char	*full_path;
	char	*temp;

	i = 0;
	path = "test_files/test";
	printf("FOPEN_MAX = %i", FOPEN_MAX);
	while (i < 50)
	{
		full_path = ft_strjoin2(path, ft_itoa(i));
		fds[i] = open(full_path, O_CREAT);
		i++;
	}
	i = 0;
	while (i < 5)
	{
		j = 0;
		while (j < FOPEN_MAX)
		{
			temp = get_next_line(fds[j]);
			printf("fd[%03i] line %i = %s",j , i + 1, temp);
			if (!temp)
				printf("\n");
			j++;
		}
		i++;
	}
	return (0);
}
