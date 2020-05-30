/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_print_str.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/28 18:15:37 by awerebea          #+#    #+#             */
/*   Updated: 2020/05/31 01:00:27 by awerebea         ###   ########.fr       */
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

wchar_t			*f_wstrdup(const wchar_t *ws)
{
	wchar_t	*dest;
	wchar_t *ws_bckp;
	size_t	len;
	size_t	i;

	ws_bckp = (wchar_t*)ws;
	len = (size_t)ws;
	while (*ws)
		ws++;
	len = ((size_t)ws - len) / 4;
	ws = ws_bckp;
	if (!(dest = malloc(sizeof(wchar_t) * (len + 1))))
		return (NULL);
	i = 0;
	while (i < len)
	{
		dest[i] = ws[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
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
	wchar_t	*str;

	count = 0;
	str = (!(wchar_t*)val) ? f_wstrdup(L"(null)") : (wchar_t*)val;
	if (!((wchar_t*)str) || !(f_chk_wstr((wchar_t*)str)))
		return (-1);
	len = (int)f_wstrlen((wchar_t*)str);
	len = ((opts->flags & 32) && len > opts->prec && val) ? opts->prec : len;
	if (opts->width > len)
	{
		if (opts->flags & 16)
		{
			count += f_putwstr_count((wchar_t*)str, len);
			while (count < opts->width)
				count += f_putchar_count(' ');
			return (count);
		}
		while (count < opts->width - len)
			count += f_putchar_count(' ');
	}
	count += (val || opts->prec >= len || !(opts->flags & 32)) ? f_putwstr_count((wchar_t*)str, len) : 0;
	(!val) ? free((wchar_t*)str) : 0;
	return (count);
}

static int		f_assist_str(char *val, t_opts *opts)
{
	int		count;
	int		len;
	char	*str;

	count = 0;
	str = (!val) ? ft_strdup("(null)") : val;
	if (!(str))
		return (-1);
	len = (int)ft_strlen(str);
	len = ((opts->flags & 32) && len > opts->prec && val) ? opts->prec : len;
	if (opts->width > len)
	{
		if (opts->flags & 16)
		{
			count += f_putstr_count(str, len);
			while (count < opts->width)
				count += f_putchar_count(' ');
			return (count);
		}
		while (count < opts->width - len)
			count += f_putchar_count(' ');
	}
	count += (val || opts->prec >= len || !(opts->flags & 32)) ? f_putstr_count(str, len) : 0;
	(!val) ? free(str) : 0;
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
