/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 22:37:28 by awerebea          #+#    #+#             */
/*   Updated: 2020/05/21 15:58:47 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*str;
	char	*ptr_c;

	str = (char *)s;
	ptr_c = NULL;
	while (*str)
	{
		if (*str == c)
			ptr_c = str;
		str++;
	}
	if (c == '\0')
		ptr_c = str;
	return (ptr_c);
}
