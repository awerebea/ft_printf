/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_print_ptr_uns_hex.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/01 19:43:02 by awerebea          #+#    #+#             */
/*   Updated: 2020/06/05 23:15:26 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_printf.h"

static int		f_print_sign(t_opts *opts)
{
	if (opts->spec == 'p' || \
			((opts->spec == 'x' || opts->spec == 'X') && (opts->flags & 2)))
		return (f_putstr_count("0x", 2, 1));
	if (opts->spec == 'd' || opts->spec == 'i' || \
			opts->spec == 'u' || opts->spec == 'x' || opts->spec == 'X')
	{
		if (opts->flags & 12)
			return (opts->flags & 8) ? \
			f_putchar_count('+', 1) : f_putchar_count(' ', 1);
	}
	return (0);
}

static int		f_flag_minus_or_zero(t_opts *opts, char *s, int val, int len)
{
	int		count;

	count = 0;
	if (opts->flags & 16)
	{
		count += f_print_sign(opts);
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
		count += f_print_sign(opts);
		while (count < opts->width - len)
			count += f_putchar_count('0', 1);
		count += ((opts->flags & 32) && !opts->prec && !val) ? \
				0 : f_putstr_count(s, len, 1);
	}
	return (count);
}

static int		f_val_zero(t_opts *opts, int len)
{
	int		count;
	int		spaces;

	count = 0;
	if (opts->spec != 'p' && (opts->flags & 12))
		opts->width--;
	if (opts->spec == 'p' || \
			((opts->spec == 'x' || opts->spec == 'X') && (opts->flags & 2)))
		opts->width -= 2;
	if (opts->prec)
		spaces = opts->width - opts->prec;
	else if (!(opts->flags & 32))
		spaces = opts->width - len;
	else
		spaces = opts->width;
	while (count < spaces)
		count += f_putchar_count(' ', 1);
	count += f_print_sign(opts);
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
	if (opts->spec != 'p' && (opts->flags & 12 || val < 0))
		opts->width--;
	if (opts->spec == 'p' || \
			((opts->spec == 'x' || opts->spec == 'X') && (opts->flags & 2)))
		opts->width -= 2;
	while (count < opts->width - opts->prec)
		count += f_putchar_count(' ', 1);
	count += f_print_sign(opts);
	while (opts->prec-- > len)
		count += f_putchar_count('0', 1);
	count += f_putstr_count(s, len, 1);
	return (count);
}

int				f_print_ptr_uns_hex(va_list ap, t_opts *opts)
{
	int				count;
	size_t			val;
	char			*s;
	int				len;

	count = 0;
	val = va_arg(ap, size_t);
	s = (opts->spec == 'u') ? f_ullitoa_base(val, 10) : f_ullitoa_base(val, 16);
	s = (opts->spec == 'X') ? f_strupper(s) : s;
	if (!s)
		return (-1);
	len = (int)ft_printf_strlen(s);
	if (opts->flags & 16 || ((opts->flags & 1) && !(opts->flags & 32)))
		count = f_flag_minus_or_zero(opts, s, val, len);
	else if (!val)
		count = f_val_zero(opts, len);
	else
		count = f_other_cases(opts, s, val, len);
	free(s);
	return (count);
}