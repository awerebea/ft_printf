/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 14:36:08 by awerebea          #+#    #+#             */
/*   Updated: 2020/05/21 15:06:06 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
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
