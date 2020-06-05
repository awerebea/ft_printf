/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_print_int.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 13:29:10 by awerebea          #+#    #+#             */
/*   Updated: 2020/06/05 12:02:26 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_printf.h"

static int		f_print_sign(t_opts *opts, int val)
{
	if ((opts->flags & 12) && val >= 0)
		return (opts->flags & 8) ? \
		f_putchar_count('+', 1) : f_putchar_count(' ', 1);
	return (val < 0) ? f_putchar_count('-', 1) : 0;
}

static int		f_flag_minus_or_zero(t_opts *opts, char *s, int val, int len)
{
	int		count;

	count = 0;
	if (opts->flags & 16)
	{
		count += f_print_sign(opts, val);
		while (opts->prec > len)
		{
			count += f_putchar_count('0', 1);
			opts->prec--;
		}
		count += ((opts->flags & 32) && !opts->prec && !val) ? \
				0 : f_putstr_count(s, len, 1);
		while (count < opts->width)
			count += f_putchar_count(' ', 1);
	}
	else if ((opts->flags & 1) && !(opts->flags & 32))
	{
		count += f_print_sign(opts, val);
		while (count < opts->width - len)
			count += f_putchar_count('0', 1);
		count += ((opts->flags & 32) && !opts->prec && !val) ? \
				0 : f_putstr_count(s, len, 1);
	}
	return (count);
}

static int		f_val_zero(t_opts *opts, int val, int len)
{
	int		count;
	int		spaces;

	count = 0;
	if (opts->flags & 12)
		opts->width--;
	if (opts->prec)
		spaces = opts->width - opts->prec;
	else if (!(opts->flags & 32))
		spaces = opts->width - len;
	else
		spaces = opts->width;
	while (count < spaces)
		count += f_putchar_count(' ', 1);
	count += f_print_sign(opts, val);
	while (opts->prec-- >= len)
		count += f_putchar_count('0', 1);
	count += (!(opts->flags & 32)) ? f_putchar_count('0', 1) : 0;
	return (count);
}

static int		f_other_cases(t_opts *opts, char *s, int val, int len)
{
	int		count;

	count = 0;
	opts->prec = (len > opts->prec) ? len : opts->prec;
	if (opts->flags & 12 || val < 0)
		opts->width--;
	while (count < opts->width - opts->prec)
		count += f_putchar_count(' ', 1);
	count += f_print_sign(opts, val);
	while (opts->prec-- > len)
		count += f_putchar_count('0', 1);
	count += f_putstr_count(s, len, 1);
	return (count);
}

int				f_print_int(va_list ap, t_opts *opts)
{
	int		count;
	int		val;
	char	*s;
	int		len;

	val = va_arg(ap, int);
	s = f_llitoa_base(val, 10);
	len = (int)ft_printf_strlen(s);
	if (val < 0)
	{
		len--;
		s++;
	}
	if (opts->flags & 16 || ((opts->flags & 1) && !(opts->flags & 32)))
		count = f_flag_minus_or_zero(opts, s, val, len);
	else if (!val)
		count = f_val_zero(opts, 0, len);
	else
		count = f_other_cases(opts, s, val, len);
	(val < 0) ? free(--s) : free(s);
	return (count);
}
