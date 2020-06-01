/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/21 14:42:35 by awerebea          #+#    #+#             */
/*   Updated: 2020/06/01 22:15:15 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

/*
** if (spec == 'p')
**     return (f_print_ptr(ap, opts));
** if (spec == 'n')
**     return (f_print_nothing(ap, opts));
** if (spec == 'f' || spec == 'F')
**     return (f_print_float(ap, opts));
** if (spec == 'g' || spec == 'G')
**     return (f_print_short_float(ap, opts));
** if (spec == 'e' || spec == 'E')
**     return (f_print_scientific(ap, opts, spec));
** if (spec == '%')
**     return (f_print_percent(ap, opts));
*/

int				f_print_argument(va_list ap, t_opts *opts, char spec)
{
	if (spec == 'c' || spec == 'C')
		return (f_print_char(ap, opts));
	if (spec == 's')
		return (f_print_str(ap, opts));
	if (spec == 'd' || spec == 'i')
		return (f_print_int(ap, opts));
	if (spec == 'u' || spec == 'x' || spec == 'X')
		return (f_print_unsig_int_hex(ap, opts, spec));
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
