/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_format.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmenigau <lmenigau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 20:05:06 by lmenigau          #+#    #+#             */
/*   Updated: 2017/04/05 20:56:15 by lmenigau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"


void	handle_sign(t_print_info *print_info, t_spec *spec)
{
	print_info->sign = '\0';
	print_info->padlen = 0;
	if (spec->sign == 1)
	{
		if (print_info->arg < 0)
			print_info->sign = '-';
		else if (print_info->arg >= 0 && spec->flags[plus])
			print_info->sign = '+';
		else if (print_info->arg > 0 && spec->flags[space])
			print_info->sign = ' ';
	}
}

void	compute_length_num(t_print_info *print_info, t_spec *spec)
{
	print_info->preclen = 0;
	print_info->arglen = numlen(print_info->arg, spec->base);
	if (print_info->arglen < spec->prec)
		print_info->preclen = spec->prec - print_info->arglen;
	if (spec->flags[hash] && spec->conv == o)
		print_info->sign = '0';
	if (spec->flags[hash] && (spec->conv == x || spec->conv == X))
		print_info->arglen++;
	if (print_info->sign != '\0')
		print_info->arglen++;
	if (print_info->arglen + print_info->preclen < spec->width)
		print_info->padlen = spec->width - print_info->arglen - print_info->preclen;
}

void	compute_length_string(t_print_info *print_info, t_spec *spec)
{
	print_info->arglen = ft_strlen((char *)print_info->arg);
	if (spec->flags[dot])
		print_info->arglen = spec->prec;
	if (print_info->arglen < spec->width)
		print_info->padlen = spec->width - print_info->arglen;
}

int		process_format(va_list ap, t_buff *buff, t_spec *spec)
{
	t_print_info	print_info;

	print_info.padchar = ' ';
	if (spec->flags[zero] && !spec->flags[minus])
		print_info.padchar = '0';
	print_info.arg = get_arg(ap, buff, spec);
	handle_sign(&print_info, spec);
	if (spec->conv > S && spec->conv < c)
		compute_length_num(&print_info, spec);
	else if (spec->conv == S || spec->conv == s)
		compute_length_string(&print_info, spec);
	return (print_arg(&print_info, spec, buff));
}
