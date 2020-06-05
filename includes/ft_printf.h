/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/23 16:26:06 by awerebea          #+#    #+#             */
/*   Updated: 2020/06/05 18:09:16 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H

# define FT_PRINTF_H
# include <stdarg.h>
# include <wchar.h>
# include <sys/types.h>

typedef struct	s_opts
{
	int		width;
	int		prec;
	int		count_already_printed;
	char	flags;
	char	subspec;
	char	spec;
}				t_opts;

int				ft_printf(const char *format, ...);
char			*ft_printf_strchr(const char *s, int c);
char			*ft_printf_strdup(const char *s);
int				ft_printf_toupper(int c);
char			*f_strupper(char *s);
size_t			ft_printf_strlen(const char *s);
char			*f_llitoa_base(ssize_t n, int base);
char			*f_ullitoa_base(unsigned long long n, int base);
int				f_isspec(const char *format, int *i, t_opts *opts);
int				f_pars_format(va_list ap, const char *format);
int				f_print_argument(va_list ap, t_opts *opts, char spec);
int				f_print_char(va_list ap, t_opts *opts);
int				f_print_str(va_list ap, t_opts *opts);
int				f_print_ptr(va_list ap, t_opts *opts);
int				f_print_int(va_list ap, t_opts *opts);
int				f_print_uns_hex(va_list ap, t_opts *opts, char spec);
int				f_putchar_count(char c, int fd);
int				f_putstr_count(char *s, int len, int fd);
int				f_putwstr_count(wchar_t *s, int len, int fd);
t_opts			f_init_opts(int count);
wchar_t			*f_wstrdup(const wchar_t *ws);

#endif
