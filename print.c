/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmenigau <lmenigau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/18 03:25:00 by lmenigau          #+#    #+#             */
/*   Updated: 2017/03/18 03:36:42 by lmenigau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ft_printf.h"

int		print_number(long arg, t_spec *spec, t_buff *buffer)
{
	if (spec->conv == d)
		ft_putnbr_base_signed(arg, buffer, spec->basestr, spec->base);
}

void	padding()
{
}

int		print_char(long arg, t_spec *spec, t_buff *buffer)
{
	if (spec->conv == c)
	{
		write_to_buff(buffer, arg);
	}

	return (0);
}

int		print_string(long arg, t_spec *spec, t_buff *buffer)
{
	return (0);
}

int		print_arg(long arg, t_spec *spec, t_buff *buffer)
{
	int		i;
	if (spec->conv > S && spec->conv < c)
		print_number(arg, spec, buffer);
	else if (spec->conv >= c)
		print_char(arg, spec, buffer);
	else if (spec->conv <= S)
		print_string(arg, spec, buffer);
	return (0);
}
