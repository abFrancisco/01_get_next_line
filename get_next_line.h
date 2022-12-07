/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falves-b <falves-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 14:51:42 by falves-b          #+#    #+#             */
/*   Updated: 2022/12/07 14:52:53 by falves-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <stdio.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 500
# endif

size_t	ft_strlen(const char *s);
void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_strchr(const char *s, int c);
char	*ft_strchrnul(const char *s, int c);
char	*ft_strndup(const char *s, size_t size);
char	*ft_strjoin(char *s1, char *s2);
void	*ft_memmove(void *dest, const void *src, size_t n);
char	*get_line(char *line, int fd);
char	*get_next_line(int fd);

#endif