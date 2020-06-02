/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_print_percent.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/02 10:53:15 by awerebea          #+#    #+#             */
/*   Updated: 2020/06/02 13:30:49 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				f_print_percent(void)
{
/*
** return ((opts->flags & 63) || opts->subspec) ? \
**     -1 : f_putchar_count('%', 0);
*/
		return (f_putchar_count('%', 0));
}
