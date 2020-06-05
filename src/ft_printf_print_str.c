/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_print_str.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/28 18:15:37 by awerebea          #+#    #+#             */
/*   Updated: 2020/06/05 21:29:10 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_printf.h"

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

static int		f_print_assist_wstr(wchar_t *str, wchar_t *val, t_opts *opts)
{
	int		count;
	int		len;

	count = 0;
	len = (int)f_wstrlen(str);
	len = ((opts->flags & 32) && len > opts->prec && val) ? opts->prec : len;
	if (opts->width > len)
	{
		if (opts->flags & 16)
		{
			count += f_putwstr_count(str, len, 1);
			while (count < opts->width)
				count += f_putchar_count(' ', 1);
			return (count);
		}
		while (count < opts->width - len)
			count += f_putchar_count(' ', 1);
	}
	if (opts->prec >= len || !(opts->flags & 32))
		count += f_putwstr_count(str, len, 1);
	if (!val)
		free(str);
	return (count);
}

static int		f_print_assist_str(char *str, char *val, t_opts *opts)
{
	int		count;
	int		len;
	int		spaces;

	count = 0;
	len = (int)ft_printf_strlen(str);
	len = ((opts->flags & 32) && len > opts->prec) ? opts->prec : len;
	if (!val && !opts->width && !(opts->flags & 32))
		return (f_putstr_count(str, (int)ft_printf_strlen(str), 1));
	if (opts->prec > len || !(opts->flags & 32))
		opts->prec = len;
	spaces = (opts->flags & 16) ? opts->width : opts->width - opts->prec;
	if (opts->flags & 16)
		count += f_putstr_count(str, opts->prec, 1);
	while (count < spaces)
		count += f_putchar_count(' ', 1);
	if (!(opts->flags & 16))
		count += f_putstr_count(str, opts->prec, 1);
	if (!val)
		free(str);
	return (count);
}

int				f_print_str(va_list ap, t_opts *opts)
{
	char	*val;
	char	*str;
	wchar_t	*wstr;

	str = NULL;
	wstr = NULL;
	val = va_arg(ap, char*);
	if (opts->subspec & 8)
	{
		wstr = (!((wchar_t*)val)) ? f_wstrdup(L"(null)") : (wchar_t*)val;
		return (!(wstr) || !(f_chk_wstr(wstr))) ? \
		-1 : f_print_assist_wstr(wstr, (wchar_t*)val, opts);
	}
	else
	{
		str = (!val) ? ft_printf_strdup("(null)") : val;
		return (!(str)) ? -1 : f_print_assist_str(str, val, opts);
	}
}
