/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/21 14:42:35 by awerebea          #+#    #+#             */
/*   Updated: 2020/05/27 23:28:36 by awerebea         ###   ########.fr       */
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

char		f_chk_flags_1(char flags)
{
	return (((flags & 17) != 17) && ((flags & 12) != 12)) ? flags : 0;
}

char		f_pars_flags(char c, char flags)
{
	return (c == '-' && !(16 & flags)) ? f_chk_flags_1(flags + 16) : 0;
	return (c == '+' && !(8 & flags)) ? f_chk_flags_1(flags + 8) : 0;
	return (c == ' ' && !(4 & flags)) ? f_chk_flags_1(flags + 4) : 0;
	return (c == '#' && !(2 & flags)) ? f_chk_flags_1(flags + 2) : 0;
	return (c == '0' && !(1 & flags)) ? f_chk_flags_1(flags + 1) : 0;
}

t_opts		f_init_opts(void)
{
	t_opts	opts;

	opts.width = 0;
	opts.precision = 0;
	opts.flags = 0;
	opts.subspec = 0;
	opts.specifier = 0;
	return (opts);
}

int			f_isspec(const char *format, int *i, t_opts *opts)
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
		return (ft_strchr("cCsdiuxXnfFgeE", format[*i])) ? 1 : 0;
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
	return (ft_strchr("cCsdiuxXnfFgeE%", format[*i])) ? 1 : 0;
}

int			f_pars_width(va_list ap, const char *format, int *i, t_opts *opts)
{
	int		width;

	width = 0;
	if (format[*i] == '*')
	{
		if ((width = va_arg(ap, int)) < 0)
		{
			width *= -1;
			opts->flags = opts->flags | 16;
			opts->flags = opts->flags & 30;
		}
		*i += 1;
	}
	else
	{
		while (ft_isdigit(format[*i]))
		{
			if ((width * 10) < width)
				return (-1);
			width = width * 10 + format[*i] - '0';
			*i += 1;
		}
	}
	return (f_isspec(format, i, opts) || format[*i] == '.') ? width : -1;
}

int			f_pars_precisn(va_list ap, const char *format, int *i, t_opts *opts)
{
	int		precision;

	precision = 0;
	opts->flags += 32;
	if (format[*i] == '*')
	{
		if ((precision = va_arg(ap, int)) < 0)
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
	return (f_isspec(format, i, opts)) ? precision : -1;
}

int			f_print_argument(va_list ap, t_opts *opts, char specifier)
{
	(void)ap;
	(void)opts;
	(void)specifier;
	return (0);
}

int			f_pars_opts(va_list ap, const char *format, int *i)
{
	t_opts	opts;

	(void)ap;
	opts = f_init_opts();
	*i += 1;
	while (ft_strchr("-+ #0", format[*i]))
	{
		if (!(opts.flags = f_pars_flags(format[*i], opts.flags)))
			return (-1);
		*i += 1;
	}
	if (format[*i] == '*' || ft_isdigit(format[*i]))
	{
		if ((opts.width = f_pars_width(ap, format, i, &opts)) < 0)
			return (-1);
	}
	if (format[*i] == '.' && format[*i + 1])
	{
		*i += 1;
		if ((opts.precision = f_pars_precisn(ap, format, i, &opts)) < 0)
			return (-1);
	}
	if (f_isspec(format, i, &opts))
		return (f_print_argument(ap, &opts, format[*i]));
	return (-1);
}

int			f_pars_format(va_list ap, const char *format)
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
			if ((tmp = f_pars_opts(ap, format, &i)) < 0)
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
	count += f_pars_format(ap, format);
	va_end(ap);
	return (count);
}
