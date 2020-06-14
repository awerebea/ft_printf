/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/28 00:25:59 by awerebea          #+#    #+#             */
/*   Updated: 2020/06/14 12:50:21 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "ft_printf.h"

int				f_putchar_count(char c, int fd)
{
	write(fd, &c, 1);
	return (1);
}

int				f_putstr_count(char *s, int len, int fd)
{
	int		count;

	count = 0;
	while (*s && count < len)
		count += f_putchar_count(*s++, fd);
	return (count);
}

int				f_putwstr_count(wchar_t *s, int len, int fd)
{
	int		count;

	count = 0;
	while (*s && count < len)
		count += f_putchar_count(*s++, fd);
	return (count);
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

char			f_isspec(const char *format, int *i, t_opts *opts)
{
	if (!format[*i])
		return (0);
	if (format[*i] == 'L')
	{
		opts->subspec += 4;
		(*i)++;
	}
	else if (format[*i] == 'l')
	{
		opts->subspec = 8;
		(*i)++;
		if (format[(*i)++] == 'l')
			opts->subspec += 4;
		*i -= (opts->subspec & 4) ? 0 : 1;
	}
	else if (format[*i] == 'h')
	{
		(*i)++;
		opts->subspec = 2;
		if (format[(*i)++] == 'h')
			opts->subspec += 1;
		*i -= (opts->subspec & 1) ? 0 : 1;
	}
	return (ft_printf_strchr("cCspdiuoxXnfFgGeE%", format[*i])) ? \
	format[*i] : 0;
}
