/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_print_char.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/28 13:45:09 by awerebea          #+#    #+#             */
/*   Updated: 2020/05/28 22:05:42 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

int				f_print_char(va_list ap, t_opts *opts)
{
	int		count;
	char	val;

	count = 0;
	if ((opts->flags & 47) || (opts->subspec & 7))
		return (-1);
	val = va_arg(ap, int);
	if ((opts->subspec & 8) && val < 0)
		return (-1);
	if (opts->width > 1)
	{
		if (opts->flags & 16)
		{
			count += f_putchar_count(val);
			while (count < opts->width)
				count += f_putchar_count(' ');
			return (count);
		}
		while (count < opts->width - 1)
			count += f_putchar_count(' ');
	}
	count += f_putchar_count(val);
	return (count);
}
