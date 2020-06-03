/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/01 20:10:12 by awerebea          #+#    #+#             */
/*   Updated: 2020/06/03 10:53:23 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_printf.h"

char			*f_llitoa_base(long long n, int base)
{
	char				*str;
	char				*symbols;
	int					i;
	long long			m;
	unsigned long long	num;

	if ((base < 2 || base > 16) || (base != 10 && n < 0))
		return (NULL);
	if (n == 0)
		return (ft_printf_strdup("0"));
	i = (n < 0) ? 2 : 1;
	m = n;
	while (m /= base)
		i++;
	if (!(symbols = ft_printf_strdup("0123456789abcdef")) || \
			!(str = malloc(sizeof(char) * (i + 1))))
		return (NULL);
	(n < 0) ? str[0] = '-' : 0;
	num = (n < 0) ? ((unsigned long long)n * -1) : (unsigned long long)n;
	str[i--] = '\0';
	str[i--] = symbols[num % base];
	while (num /= base)
		str[i--] = symbols[num % base];
	free(symbols);
	return (str);
}
