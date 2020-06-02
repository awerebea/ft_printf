/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_print_uns_int_hex.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/01 19:43:02 by awerebea          #+#    #+#             */
/*   Updated: 2020/06/02 10:37:31 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

static int		f_print_assist(t_opts *opts, char *s, size_t val, int len)
{
	int		count;

	count = 0;
	if (opts->flags & 8)
		count += f_putchar_count('+', 0);
	if (opts->flags & 4)
		count += f_putchar_count(' ', 0);
	if (val == 0)
		opts->prec++;
	if (opts->flags & 1)
		opts->prec = opts->width;
	while (opts->prec-- > len)
		count += f_putchar_count('0', 0);
	if (val != 0 || !(opts->flags & 32))
		count += f_putstr_count(s, len, 0);
	return (count);
}

static int		f_chk_flags(t_opts *opts, char *s, size_t val, int len)
{
	int		count;

	count = 0;
	if (opts->flags & 16)
	{
		count += f_print_assist(opts, s, val, len);
		while (count < opts->width)
			count += f_putchar_count(' ', 0);
	}
	else if (opts->flags & 1)
		count += f_print_assist(opts, s, val, len);
	else
	{
		(opts->flags & 12) ? opts->width-- : 0;
		if ((opts->width - len) > (opts->prec - len))
		{
			while (opts->width-- > ((opts->prec > len) ? \
						opts->prec : len))
				count += f_putchar_count(' ', 0);
		}
		count += f_print_assist(opts, s, val, len);
	}
	return (count);
}

static char		*f_strupper(char *s)
{
	int				len;
	char			*dest;

	len = ft_strlen(s);
	if (!(dest = malloc((sizeof(char) * len + 1))))
		return (NULL);
	while (*s)
		*dest++ = ft_toupper(*s++);
	*dest = '\0';
	free(s - len);
	return (dest - len);
}

int				f_print_ptr_uns_hex(va_list ap, t_opts *opts, char spec)
{
	int				count;
	size_t			val;
	char			*s;
	int				len;

	if ((opts->flags & 2) || ((opts->flags & 12) == 12) || \
			((opts->flags & 33) == 33))
		return (-1);
	count = 0;
	val = va_arg(ap, size_t);
	s = (spec == 'u') ? f_llitoa_base(val, 10) : f_llitoa_base(val, 16);
	s = (spec == 'X') ? f_strupper(s) : s;
	if (spec == 'p' && !val)
	{
		free(s);
		s = ft_strdup("0x0");
	}
	if (!s)
		return (-1);
	if (spec == 'p' && val)
		count += f_putstr_count("0x", 2, 0);
	len = (int)ft_strlen(s);
	count += f_chk_flags(opts, s, val, len);
	free(s);
	return (count);
}
