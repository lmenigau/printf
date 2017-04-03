/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmenigau <lmenigau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/18 03:25:00 by lmenigau          #+#    #+#             */
/*   Updated: 2017/04/03 20:40:24 by lmenigau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ft_printf.h"

void	padding(long arg, t_spec *spec, t_buff *buffer)
{
	size_t	i;
	long	len;
	size_t	arglen;
	char	c;

	i = 1;
	c = ' ';
	if (spec->conv > S && spec->conv < c)
		arglen = numlen(arg, spec->base);
	if (arg < 0 && spec->sign == 1)
		arglen++;
	else if (spec->conv == s)
		arglen = ft_strlen((char *)arg) - 1;
	if ((len = spec->width - arglen) <= 0)
		return ;
	if (spec->flags[zero])
		c = '0';
	while (i < (size_t)len)
	{
		buffer->buff[buffer->count % BUFF_SIZE] = c;
		buffer->count++;
		if (buffer->count % BUFF_SIZE == 0)
			write(1, buffer->buff, BUFF_SIZE);
		i++;
	}
}

int		print_number(long arg, t_spec *spec, t_buff *buffer)
{
	if (spec->conv == d || spec->conv == i || spec->conv == D)
		ft_putnbr_base_signed(arg, buffer, spec->basestr, spec->base);
	else
		ft_putnbr_base_unsigned(arg, buffer, spec->basestr, spec->base);
	return (0);
}


void	put_str_buff(t_buff *buff, char *str)
{
	size_t  i;

	i = 0;
	while (str[i])
	{
		buff->buff[buff->count % BUFF_SIZE] = str[i];
		buff->count++;
		if (buff->count % BUFF_SIZE == 0)
			write(1, buff->buff, BUFF_SIZE);
		i++;
	}
}

int		print_char(long arg, t_spec *spec, t_buff *buffer)
{
	if (spec->conv == c && spec->mod != l)
		write_to_buff(buffer, arg);
	else if ((spec->conv == c && spec->mod == l) || spec->conv == C)
		write_to_buff(buffer, arg);
	return (0);
}

int		print_string(long arg, t_spec *spec, t_buff *buffer)
{
	if (spec->conv == s)
	{
		put_str_buff(buffer, (char *)arg);
	}
	return (0);
}

int		print_arg(long arg, t_spec *spec, t_buff *buffer)
{
	if (!spec->flags[minus])
		padding(arg, spec, buffer);
	if (spec->conv > S && spec->conv < c)
		print_number(arg, spec, buffer);
	else if (spec->conv >= c)
		print_char(arg, spec, buffer);
	else if (spec->conv <= S)
		print_string(arg, spec, buffer);
	if (spec->flags[minus])
		padding(arg, spec, buffer);
	return (0);
}
