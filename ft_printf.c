/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/21 14:42:35 by awerebea          #+#    #+#             */
/*   Updated: 2020/05/28 18:16:44 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

/*
** if (specifier == 'p')
**     return (f_print_ptr(ap, opts));
** if (specifier == 'd' || specifier == 'i')
**     return (f_print_int(ap, opts));
** if (specifier == 'u')
**     return (f_print_unsig_int(ap, opts));
** if (specifier == 'x' || specifier == 'X')
**     return (f_print_hex(ap, opts, specifier));
** if (specifier == 'n')
**     return (f_print_nothing(ap, opts));
** if (specifier == 'f' || specifier == 'F')
**     return (f_print_float(ap, opts));
** if (specifier == 'g' || specifier == 'G')
**     return (f_print_short_float(ap, opts));
** if (specifier == 'e' || specifier == 'E')
**     return (f_print_scientific(ap, opts, specifier));
** if (specifier == '%')
**     return (f_print_percent(ap, opts));
*/

int				f_print_argument(va_list ap, t_opts *opts, char specifier)
{
	if (specifier == 'c' || specifier == 'C')
		return (f_print_char(ap, opts));
	if (specifier == 's')
		return (f_print_str(ap, opts));
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
