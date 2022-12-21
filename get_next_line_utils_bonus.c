/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falves-b <falves-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 15:28:31 by falves-b          #+#    #+#             */
/*   Updated: 2022/12/21 14:31:10 by falves-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void			*mem;
	unsigned char	*tmp;
	size_t			n;

	mem = malloc(nmemb * size);
	if (!mem)
		return (NULL);
	tmp = (unsigned char *)mem;
	n = nmemb * size;
	while (n--)
		*tmp++ = 0;
	return (mem);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s != '\0')
	{
		if (c == *s)
			return ((char *)s);
		s++;
	}
	if (c == *s)
		return ((char *)s);
	return ((void *)0);
}

char	*ft_strchrnul(const char *s, int c)
{
	char	*ptr;

	ptr = ft_strchr(s, c);
	if (!ptr)
		ptr = ft_strchr(s, '\0');
	return (ptr);
}

char	*ft_strndup(const char *s, size_t size)
{
	char			*mem;
	unsigned int	i;
	int				strlen;

	mem = ft_calloc(1, size + 1);
	if (!mem)
		return (NULL);
	strlen = 0;
	while (s[strlen] != '\0')
		strlen++;
	i = 0;
	while (i < size && s[i] != '\0')
	{
		mem[i] = s[i];
		i++;
	}
	mem[i] = '\0';
	return (mem);
}
