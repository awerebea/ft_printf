/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_print_str.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/28 18:15:37 by awerebea          #+#    #+#             */
/*   Updated: 2020/05/29 20:07:24 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

static int		f_chk_wstr(wchar_t *ws)
{
	while (*ws)
	{
		if (*ws > 127)
			return (0);
		ws++;
	}
	return (1);
}

static size_t	f_wstrlen(wchar_t *s)
{
	size_t	start;

	start = (size_t)s;
	while (*s)
		s++;
	return (((size_t)s - start) / 4);
}

static int		f_assist_wstr(wchar_t *val, t_opts *opts)
{
	int		count;
	int		len;

	count = 0;
	if (!(f_chk_wstr((wchar_t*)val)))
		return (-1);
	len = (int)f_wstrlen((wchar_t*)val);
	if ((opts->flags & 32) && opts->precision < len)
		len = opts->precision;
	if (opts->width > len)
	{
		if (opts->flags & 16)
		{
			count += f_putwstr_count((wchar_t*)val, len);
			while (count < opts->width)
				count += f_putchar_count(' ');
			return (count);
		}
		while (count < opts->width - len)
			count += f_putchar_count(' ');
	}
	count += f_putwstr_count((wchar_t*)val, len);
	return (count);
}

static int		f_assist_str(char *val, t_opts *opts)
{
	int		count;
	int		len;

	count = 0;
	if (!val)
		val = "(null)";
	len = (int)ft_strlen(val);
	if ((opts->flags & 32) && opts->precision < len)
		len = opts->precision;
	if (opts->width > len)
	{
		if (opts->flags & 16)
		{
			count += f_putstr_count(val, len);
			while (count < opts->width)
				count += f_putchar_count(' ');
			return (count);
		}
		while (count < opts->width - len)
			count += f_putchar_count(' ');
	}
	count += f_putstr_count(val, len);
	return (count);
}

int				f_print_str(va_list ap, t_opts *opts)
{
	char	*val;

	if ((opts->flags & 15) || (opts->subspec & 7))
		return (-1);
	val = va_arg(ap, char*);
	return (opts->subspec & 8) ? f_assist_wstr((wchar_t*)val, opts) : \
	f_assist_str(val, opts);
}
