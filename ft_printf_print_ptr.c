/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_print_ptr.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/02 09:14:47 by awerebea          #+#    #+#             */
/*   Updated: 2020/06/02 09:56:10 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

static int		f_print_assist(t_opts *opts, char *s, size_t val, int len)
{
	int		count;

	count = 0;
	if (opts->flags & 8)
		count += f_putchar_count('+', 0);
	if (opts->flags & 4)
		count += f_putchar_count(' ', 0);
	if (val == 0)
		opts->prec++;
	if (opts->flags & 1)
		opts->prec = opts->width;
	while (opts->prec-- > len)
		count += f_putchar_count('0', 0);
	if (val != 0 || !(opts->flags & 32))
		count += f_putstr_count(s, len, 0);
	return (count);
}

static int		f_print_int_chk_flags(t_opts *opts, char *s, \
										size_t val, int len)
{
	int		count;

	count = 0;
	if (opts->flags & 16)
	{
		count += f_print_assist(opts, s, val, len);
		while (count < opts->width)
			count += f_putchar_count(' ', 0);
	}
	else if (opts->flags & 1)
		count += f_print_assist(opts, s, val, len);
	else
	{
		(opts->flags & 12) ? opts->width-- : 0;
		if ((opts->width - len) > (opts->prec - len))
		{
			while (opts->width-- > ((opts->prec > len) ? \
						opts->prec : len))
				count += f_putchar_count(' ', 0);
		}
		count += f_print_assist(opts, s, val, len);
	}
	return (count);
}

int				f_print_ptr(va_list ap, t_opts *opts)
{
	int				count;
	size_t			val;
	char			*s;
	int				len;

	if ((opts->flags & 2) || ((opts->flags & 12) == 12) || \
			((opts->flags & 33) == 33))
		return (-1);
	val = va_arg(ap, size_t);
	s = f_llitoa_base((unsigned long long)val, 16);
	if (!s)
		return (-1);
	len = (int)ft_strlen(s);
	count = f_print_int_chk_flags(opts, s, val, len);
	free(s);
	return (count);
}
