/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/23 16:26:06 by awerebea          #+#    #+#             */
/*   Updated: 2020/05/27 19:03:21 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H

# define FT_PRINTF_H

typedef struct	s_opts
{
	int		width;
	int		precision;
	char	flags;
	char	specifier;
}				t_opts;

int				ft_printf(const char *, ...);

#endif
