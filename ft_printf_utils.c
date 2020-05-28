/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/28 00:25:59 by awerebea          #+#    #+#             */
/*   Updated: 2020/05/28 14:34:17 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

int				f_putchar_count(char c)
{
	write(0, &c, 1);
	return (1);
}

t_opts			f_init_opts(int count)
{
	t_opts	opts;

	opts.width = 0;
	opts.precision = 0;
	opts.count_already_printed = count;
	opts.flags = 0;
	opts.subspec = 0;
	opts.specifier = 0;
	return (opts);
}

int				f_isspec(const char *format, int *i, t_opts *opts)
{
	if (format[*i] == 'l')
	{
		*i += 1;
		opts->subspec = 8;
		if (format[*i] == 'l')
		{
			*i += 1;
			opts->subspec = 4;
			return (ft_strchr("diuxXn", format[*i])) ? 1 : 0;
		}
		return (ft_strchr("cCspdiuxXnfFgGeE", format[*i])) ? 1 : 0;
	}
	if (format[*i] == 'h')
	{
		*i += 1;
		opts->subspec = 2;
		if (format[*i] == 'h')
		{
			*i += 1;
			opts->subspec = 1;
			return (ft_strchr("diuxXn", format[*i])) ? 1 : 0;
		}
		return (ft_strchr("diuxXn", format[*i])) ? 1 : 0;
	}
	return (ft_strchr("cCspdiuxXnfFgGeE%", format[*i])) ? 1 : 0;
}
