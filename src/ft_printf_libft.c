/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_libft.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/03 10:35:45 by awerebea          #+#    #+#             */
/*   Updated: 2020/06/05 12:35:16 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char			*ft_printf_strjoin(char const *s1, char const *s2)
{
	char	*result;
	size_t	len;
	size_t	start;

	if (!s1 || !s2)
		return (NULL);
	start = (size_t)s1;
	while (*s1)
		s1++;
	len = ((size_t)s1 - start);
	s1 -= ((size_t)s1 - start);
	start = (size_t)s2;
	while (*s2)
		s2++;
	len += ((size_t)s2 - start);
	s2 -= ((size_t)s2 - start);
	if (!(result = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (*s1)
		*result++ = *s1++;
	while (*s2)
		*result++ = *s2++;
	*result = '\0';
	result -= len;
	return (result);
}

char			*ft_printf_strchr(const char *s, int c)
{
	while (*s != c)
	{
		if (!*s)
			return (NULL);
		s++;
	}
	return ((char *)s);
}

char			*ft_printf_strdup(const char *s)
{
	char	*dest;
	size_t	len;

	len = (size_t)s;
	while (*s)
		s++;
	len = (size_t)s - len;
	s -= len;
	if (!(dest = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (*s)
		*dest++ = (char)*s++;
	*dest = '\0';
	dest -= len;
	return (dest);
}

size_t			ft_printf_strlen(const char *s)
{
	size_t	start;

	start = (size_t)s;
	while (*s)
		s++;
	return ((size_t)s - start);
}

int				ft_printf_toupper(int c)
{
	if (c >= 97 && c <= 122)
		return (c - 32);
	return (c);
}
