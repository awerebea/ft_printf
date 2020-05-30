/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_print_int.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 13:29:10 by awerebea          #+#    #+#             */
/*   Updated: 2020/05/30 18:03:22 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

char			*f_llitoa_base(long long n, int base)
{
	char				*str;
	char				*symbols;
	int					i;
	long long			m;
	unsigned long long	num;

	if ((base < 2 || base > 16) || (base != 10 && n < 0))
		return (NULL);
	if (n == 0)
		return (ft_strdup("0"));
	i = (n < 0) ? 2 : 1;
	m = n;
	while (m /= base)
		i++;
	if (!(symbols = ft_strdup("0123456789ABCDEF")) || \
			!(str = malloc(sizeof(char) * (i + 1))))
		return (NULL);
	(n < 0) ? str[0] = '-' : 0;
	num = (n < 0) ? ((unsigned long long)n * -1) : (unsigned long long)n;
	str[i--] = '\0';
	str[i--] = symbols[num % base];
	while (num /= base)
		str[i--] = symbols[num % base];
	free(symbols);
	return (str);
}

static int		f_print_int_assist(t_opts *opts, char *s, int val, int len)
{
	int		count;

	count = 0;
	if ((opts->flags & 8) && val >= 0)
		count += f_putchar_count('+');
	if ((opts->flags & 4) && val >= 0)
		count += f_putchar_count(' ');
	if (val < 0)
		count += f_putchar_count('-');
	if (val == 0)
		opts->precision++;
	if (opts->flags & 1)
		opts->precision = opts->width;
	while (opts->precision-- > len)
		count += f_putchar_count('0');
	if (val != 0 || !(opts->flags & 32))
		count += (val < 0) ? f_putstr_count(++s, len) : f_putstr_count(s, len);
	return (count);
}

static int		f_print_int_chk_flags(t_opts *opts, char *s, int val, int len)
{
	int		count;

	count = 0;
	if (opts->flags & 16)
	{
		count += f_print_int_assist(opts, s, val, len);
		while (count < opts->width)
			count += f_putchar_count(' ');
	}
	else if (opts->flags & 1)
		count += f_print_int_assist(opts, s, val, len);
	else
	{
		(val < 0 || (opts->flags & 12)) ? opts->width-- : 0;
		if ((opts->width - len) > (opts->precision - len))
		{
			while (opts->width-- > ((opts->precision > len) ? \
						opts->precision : len))
				count += f_putchar_count(' ');
		}
		count += f_print_int_assist(opts, s, val, len);
	}
	return (count);
}

int				f_print_int(va_list ap, t_opts *opts)
{
	int		count;
	int		val;
	char	*s;
	int		len;

	if ((opts->flags & 2) || ((opts->flags & 12) == 12) || \
			((opts->flags & 33) == 33))
		return (-1);
	val = va_arg(ap, int);
	s = f_llitoa_base(val, 10);
	len = (int)ft_strlen(s);
	if (val < 0)
		len--;
	count = f_print_int_chk_flags(opts, s, val, len);
	free(s);
	return (count);
}
