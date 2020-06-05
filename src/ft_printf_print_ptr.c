/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_print_ptr.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 12:43:49 by awerebea          #+#    #+#             */
/*   Updated: 2020/06/05 13:39:19 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_printf.h"

static int		f_print_sign(t_opts *opts)
{
	if (opts->flags & 12)
		return (opts->flags & 8) ? \
		f_putchar_count('+', 1) : f_putchar_count(' ', 1);
	return (0);
}

static int		f_flag_minus_or_zero(t_opts *opts, char *s, int len)
{
	int		count;

	count = 0;
	if (opts->flags & 16)
	{
		count += f_print_sign(opts);
		count += f_putstr_count("0x", 2, 1);
		while (opts->prec > len - 2)
		{
			count += f_putchar_count('0', 1);
			opts->prec--;
		}
		count += f_putstr_count(s, len, 1);
		while (count < opts->width)
			count += f_putchar_count(' ', 1);
	}
	else if ((opts->flags & 1) && !(opts->flags & 32))
	{
		count += f_print_sign(opts);
		count += f_putstr_count("0x", 2, 1);
		while (count < opts->width - len - 2)
			count += f_putchar_count('0', 1);
		count += f_putstr_count(s, len, 1);
	}
	return (count);
}

static int		f_other_cases(t_opts *opts, char *s, int len)
{
	int		count;

	count = 0;
	opts->prec = (len > opts->prec) ? len : opts->prec;
	if (opts->flags & 12)
		opts->width--;
	while (count < opts->width - opts->prec - 2)
		count += f_putchar_count(' ', 1);
	count += f_print_sign(opts);
	count += f_putstr_count("0x", 2, 1);
	while (opts->prec-- > len)
		count += f_putchar_count('0', 1);
	count += f_putstr_count(s, len, 1);
	return (count);
}

int				f_print_ptr(va_list ap, t_opts *opts)
{
	int				count;
	size_t			val;
	char			*s;
	int				len;

	count = 0;
	val = va_arg(ap, size_t);
	if (!val)
		return (f_putstr_count("0x0", 3, 1));
	if (!(s = f_ullitoa_base(val, 16)))
		return (-1);
	len = (int)ft_printf_strlen(s);
	if (opts->flags & 16 || ((opts->flags & 1) && !(opts->flags & 32)))
		count = f_flag_minus_or_zero(opts, s, len);
	else
		count = f_other_cases(opts, s, len);
	free(s);
	return (count);
}
