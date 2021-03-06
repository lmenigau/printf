/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_format.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmenigau <lmenigau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 20:05:06 by lmenigau          #+#    #+#             */
/*   Updated: 2017/04/13 03:56:54 by lmenigau         ###   ########.fr       */
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
		else if (print_info->arg >= 0 && spec->flags[space])
			print_info->sign = ' ';
	}
}

void	compute_length_num(t_print_info *print_info, t_spec *spec)
{
	print_info->preclen = 0;
	print_info->arglen = numlen(print_info->arg, spec->base);
	if (print_info->arg == 0 && spec->flags[dot] && spec->prec == 0 &&
			!(spec->flags[hash] && spec->conv == o))
		print_info->arglen = 0;
	if (print_info->arglen < spec->prec)
		print_info->preclen = spec->prec - print_info->arglen;
	if (spec->flags[hash] && spec->base == 8 && print_info->arg != 0 &&
			!print_info->preclen)
		print_info->preclen = 1;
	if (spec->flags[hash] &&
			(spec->conv == x || spec->conv == X || spec->conv == p))
		print_info->arglen += 2;
	if (print_info->sign != '\0')
		print_info->arglen++;
	if (print_info->arglen + print_info->preclen < spec->width)
		print_info->padlen = spec->width - print_info->arglen -
			print_info->preclen;
}

void	compute_length_string(t_print_info *print_info, t_spec *spec)
{
	if ((void *)print_info->arg != NULL)
	{
		if ((spec->conv == s && spec->mod == l) || spec->conv == S)
			print_info->arglen = wchar_len((wchar_t *)print_info->arg);
		else if (spec->conv == s)
			print_info->arglen = ft_strlen((char *)print_info->arg);
	}
	if (print_info->arg == 0)
		spec->width = 0;
	if (spec->flags[dot] && spec->prec < print_info->arglen)
		print_info->arglen = spec->prec;
	if (print_info->arglen < spec->width)
		print_info->padlen = spec->width - print_info->arglen;
}

int		process_format(va_list ap, t_buff *buff, t_spec *spec, char convchar)
{
	t_print_info	print_info;

	print_info.padchar = ' ';
	if (spec->width < 0)
	{
		spec->flags[minus] = 1;
		spec->width = -spec->width;
	}
	if (spec->prec < 0)
		spec->flags[dot] = 0;
	if (spec->flags[zero] && !spec->flags[minus] && !spec->flags[dot])
		print_info.padchar = '0';
	if (spec->conv != nil)
		print_info.arg = get_arg(ap, spec);
	else
		print_info.arg = convchar;
	handle_sign(&print_info, spec);
	if (spec->conv > S && spec->conv < c)
		compute_length_num(&print_info, spec);
	else if (spec->conv == S || spec->conv == s)
		compute_length_string(&print_info, spec);
	else if (spec->conv >= c && spec->width > 0)
		print_info.padlen = spec->width - 1;
	return (print_arg(&print_info, spec, buff));
}
