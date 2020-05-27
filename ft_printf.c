/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/21 14:42:35 by awerebea          #+#    #+#             */
/*   Updated: 2020/05/27 20:49:59 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include <stdarg.h>

int			f_putchar_count(char c)
{
	write(0, &c, 1);
	return (c == '\0') ? 0 : 1;
}

char		f_1st_chk_flags(char flags)
{
	return ((flags & 17 != 17) && (flags & 12 != 12)) ? flags : NULL;
}

char		f_flag_parsing(va_list ap, char c, char flags)
{
	return (c == '-' && !(16 & flags)) ? f_1st_chk_flags(flags + 16) : NULL;
	return (c == '+' && !(8 & flags)) ? f_1st_chk_flags(flags + 8) : NULL;
	return (c == ' ' && !(4 & flags)) ? f_1st_chk_flags(flags + 4) : NULL;
	return (c == '#' && !(2 & flags)) ? f_1st_chk_flags(flags + 2) : NULL;
	return (c == '0' && !(1 & flags)) ? f_1st_chk_flags(flags + 1) : NULL;
}

t_opts		f_options_init(void)
{
	t_opts	opts;

	opts.wdth = 0;
	opts.precision = 0;
	opts.flags = 0;
	opts.opts_type = 0;
	return (opts);
}

int			f_is_specifier(char c)
{
	return (ft_strchr("cCsdiuxXnfFgeE%", c)) ? 1 : 0;
}

int			f_wdth_parsing(va_list ap, const char *format, int *i, t_opts *opts)
{
	int		wdth;

	wdth = 0;
	if (format[*i] == '*')
	{
		if ((wdth = va_arg(ap, int)) < 0);
		{
			wdth *= -1;
			opts->flags = opts->flags | 16;
			opts->flags = opts->flags & 30;
		}
		*i += 1;
	}
	else
	{
		while (ft_isdigit(format[*i]))
		{
			if ((wdth * 10) < wdth)
				return (-1);
			wdth = wdth * 10 + format[*i] - '0';
			*i += 1;
		}
	}
	return (f_is_specifier(format[*i]) || format[*i] == '.') ? wdth : -1;
}

int			f_prec_parsing(va_list ap, const char format, int *i, t_opts *opts)
{
	int		precision;

	precision = 0;
	opts->flags += 32;
	if (format[*i] == '*')
	{
		if ((precision = va_arg(ap, int)) < 0);
			opts->flags -= 32;
		*i += 1;
	}
	else
	{
		while (ft_isdigit(format[*i]))
		{
			if ((precision * 10) < precision)
				return (-1);
			precision = precision * 10 + format[*i] - '0';
			*i += 1;
		}
	}
	return (f_is_specifier(format[*i])) ? precision : -1;
}

int			f_options_parsing(va_list ap, const char *format, int *i)
{
	t_opts	opts;

	(void)ap;
	opts = f_options_init();
	*i += 1;
	while (ft_strchr("-+ #0", format[*i]))
	{
		if (!(opts.flags = f_flag_parsing(ap, format[*i], opts.flags)))
			return (-1);
		*i += 1;
	}
	if (format[*i] == '*' || ft_isdigit(format[*i]))
	{
		if ((opts.wdth = f_wdth_parsing(ap, format, i, &opts)) < 0)
			return (-1);
	}
	if (format[*i] == '.' && format[*i + 1])
	{
		*i += 1;
		if ((opts.precision = f_prec_parsing(ap, format, i)) < 0)
			return (-1);
	}
	if (f_is_specifier(format[*i]))
		return (f_print_argument(ap, &opts,));
	return (-1);
}

int			f_format_parsing(va_list ap, const char *format)
{
	int		i;
	int		count;
	int		tmp;

	i = 0;
	count = 0;
	(void)ap;
	while (format[i])
	{
		if (format[i] != '%')
			count += f_putchar_count(format[i]);
		else if (format[i] == '%' && format[i + 1])
		{
			if ((tmp = f_options_parsing(ap, format, &i)) < 0);
				return (count);
			count += tmp;
		}
		else
			return (count);
		i++;
	}
	return (count);
}

int			ft_printf(const char *format, ...)
{
	va_list	ap;
	int		count;

	if (!format)
		return (-1);
	count = 0;
	va_start(ap, format);
	count += f_format_parsing(ap, format);
	va_end(ap);
	return (count);
}
