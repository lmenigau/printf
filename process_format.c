/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_format.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmenigau <lmenigau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 20:05:06 by lmenigau          #+#    #+#             */
/*   Updated: 2017/04/03 22:03:11 by lmenigau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"


int		process_format(va_list ap, t_buff *buff, t_spec *spec)
{
	t_print_info	print_info;

	print_info.sign = '\0';
	print_info.padlen = 0;
	print_info.arg = get_arg(ap, buff, spec);
	if (spec->sign == 1)
	{
		if (print_info.arg < 0)
		print_info.sign = '-';
		else if (print_info.arg > 0 && spec->flags[space])
		print_info.sign = ' ';
		else if (print_info.arg > 0 && spec->flags[plus])
		print_info.sign = '+';
	}
	if (print_info.sign != '\0')
		print_info.arglen++;
	if (spec->conv > S && spec->conv < c)
		print_info.arglen = numlen(print_info.arg, spec->base);
	else if ((spec->conv == S || spec->conv == s) && spec->flags[dot] == 0)
		print_info.arglen = ft_strlen((char *)print_info.arg) - 1;
	else if ((spec->conv == S || spec->conv == s) && spec->flags[dot] == 1)
		print_info.arglen = spec->prec;
	if (print_info.arglen < spec->width)
		print_info.padlen = spec->width - print_info.arglen - spec->prec;
	return (print_arg(print_info.arg, spec, buff));
}
