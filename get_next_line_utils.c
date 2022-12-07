/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falves-b <falves-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 13:05:34 by falves-b          #+#    #+#             */
/*   Updated: 2022/12/07 13:14:07 by falves-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


/*void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*mem;

	mem = malloc(nmemb * size);
	if (!mem)
		return (NULL);
	ft_memset(mem, 0, nmemb * size);
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

static char	*ft_strchrnul(const char *s, int c)
{
	char	*ptr;

	ptr = ft_strchr(s, c);
	if (!ptr)
		ptr = ft_strchr(s, '\0');
	return (ptr);
}

char	*ft_strdup(const char *s)// CHANGE THIS TO STRNDUP
{
	int		size;
	char	*mem;

	size = ft_strlen(s) + 1;
	mem = malloc(size);
	if (!mem)
		return (NULL);
	ft_strlcpy(mem, s, size);
	return (mem);
}*/
