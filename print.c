/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmenigau <lmenigau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/18 03:25:00 by lmenigau          #+#    #+#             */
/*   Updated: 2017/04/11 19:06:58 by lmenigau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	put_str_buff(t_buff *buff, char *str, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		buff->buff[buff->count % BUFF_SIZE] = str[i];
		buff->count++;
		if (buff->count % BUFF_SIZE == 0)
			write(1, buff->buff, BUFF_SIZE);
		i++;
	}
}

int 	put_wstr_buff(t_buff *buff, wchar_t *str, size_t len)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0' && i < len)
	{
		if (check_utf8(buff, str[i]) == -1)
			return (-1);
		i++;
	}
	return (0);
}

void	padding(int padlen, char padchar, t_buff *buffer)
{
	size_t	i;

	i = 0;
	while (i < (size_t)padlen)
	{
		buffer->buff[buffer->count % BUFF_SIZE] = padchar;
		buffer->count++;
		if (buffer->count % BUFF_SIZE == 0)
			write(1, buffer->buff, BUFF_SIZE);
		i++;
	}
}

int		print_number(t_print_info *print_info, t_spec *spec, t_buff *buffer)
{
	if (spec->flags[dot] && print_info->arg == 0 && spec->prec == 0 &&
			!(spec->flags[hash] && spec->base == 8))
		return (0);
	if (!spec->flags[zero])
	{
		if ((spec->flags[hash] && (spec->conv == x) &&
					(print_info->arg != 0)) || spec->conv == p)
			put_str_buff(buffer, "0x", 2);
		if (spec->flags[hash] && spec->conv == X && print_info->arg != 0)
			put_str_buff(buffer, "0X", 2);
		if (print_info->sign != '\0')
			write_to_buff(buffer, print_info->sign);
	}
	if (print_info->preclen > 0)
		padding(print_info->preclen, '0', buffer);
	if (spec->conv == d || spec->conv == i || spec->conv == D)
		ft_putnbr_base_signed(print_info->arg, buffer, spec->basestr,
				spec->base);
	else
		ft_putnbr_base_unsigned(print_info->arg, buffer, spec->basestr,
				spec->base);
	return (0);
}

int		print_char(long arg, t_spec *spec, t_buff *buffer)
{
	if ((spec->conv == c && spec->mod != l) || spec->conv == nil)
		write_to_buff(buffer, arg);
	else if ((spec->conv == c && spec->mod == l) || spec->conv == C)
	{
		return (check_utf8(buffer, (wchar_t)arg));
	}
	return (0);
}

int		print_string(t_print_info *print_info, t_spec *spec, t_buff *buffer)
{
	if ((void *)print_info->arg == NULL)
	{
		put_str_buff(buffer, "(null)", 6);
		return (0);
	}
	if ((spec->conv == s && spec->mod == l) || spec->conv == S)
		put_wstr_buff(buffer, (wchar_t *)print_info->arg, print_info->arglen);
	else if (spec->conv == s)
		put_str_buff(buffer, (char *)print_info->arg, print_info->arglen);
	return (0);
}

int		print_arg(t_print_info *print_info, t_spec *spec, t_buff *buffer)
{
	int		error_ret;

	error_ret = 0;
	if (spec->flags[zero])
	{
		if ((spec->flags[hash] && (spec->conv == x) &&
					(print_info->arg != 0)) || spec->conv == p)
			put_str_buff(buffer, "0x", 2);
		if (spec->flags[hash] && spec->conv == X && print_info->arg != 0)
			put_str_buff(buffer, "0X", 2);
		if (print_info->sign != '\0')
			write_to_buff(buffer, print_info->sign);
	}
	if (!spec->flags[minus])
		padding(print_info->padlen, print_info->padchar, buffer);
	if (spec->conv > S && spec->conv < c)
		print_number(print_info, spec, buffer);
	else if (spec->conv >= c)
		error_ret = print_char(print_info->arg, spec, buffer);
	else if (spec->conv <= S)
		error_ret = print_string(print_info, spec, buffer);
	if (spec->flags[minus])
		padding(print_info->padlen, print_info->padchar, buffer);
	if (error_ret == -1)
		return (-1);
	return (0);
}
