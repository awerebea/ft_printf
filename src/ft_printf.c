/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/21 14:42:35 by awerebea          #+#    #+#             */
/*   Updated: 2020/06/05 19:21:19 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** if (opts->spec == 'n')
**     return (f_print_nothing(ap, opts));
** if (opts->spec == 'f' || opts->spec == 'F')
**     return (f_print_float(ap, opts));
** if (opts->spec == 'g' || opts->spec == 'G')
**     return (f_print_short_float(ap, opts));
** if (opts->spec == 'e' || opts->spec == 'E')
**     return (f_print_scientific(ap, opts, opts->spec));
*/

int				f_print_argument(va_list ap, t_opts *opts)
{
	if (opts->spec == 'c' || opts->spec == 'C')
		return (f_print_char(ap, opts));
	if (opts->spec == 's')
		return (f_print_str(ap, opts));
	if (opts->spec == 'p')
		return (f_print_ptr(ap, opts));
	if (opts->spec == 'd' || opts->spec == 'i')
		return (f_print_int(ap, opts));
	if (opts->spec == 'u' || opts->spec == 'x' || opts->spec == 'X')
		return (f_print_uns_hex(ap, opts));
	if (opts->spec == '%')
		return (f_putchar_count('%', 1));
	return (0);
}

int				ft_printf(const char *format, ...)
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

t_opts			f_init_opts(int count)
{
	t_opts	opts;

	opts.width = 0;
	opts.prec = 0;
	opts.count_already_printed = count;
	opts.flags = 0;
	opts.subspec = 0;
	opts.spec = 0;
	return (opts);
}
