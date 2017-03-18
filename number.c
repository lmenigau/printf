/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   number.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmenigau <lmenigau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/18 03:29:02 by lmenigau          #+#    #+#             */
/*   Updated: 2017/03/18 04:17:12 by lmenigau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		numlen(long n, int base)
{
	int		len;

	len = 0;
	while (n /= base)
		len++;
	return len;
}

void	ft_putnbr_base_signed(long n, t_buff *buffer, char *basestr, int base)
{
	long	pow;
	int		neg;

	pow = 1;
	neg = 1;
	while (n / pow >= base || n / pow <= -base)
		pow *= base;
	if (n < 0)
	{
		write_to_buff(buffer, '-');
		neg = -1;
	}
	while (pow)
	{
		write_to_buff(buffer, basestr[(neg * (n / pow))]);
		n %= pow;
		pow /= base;
	}
}
void	ft_putnbr_base_unsigned(unsigned long n, t_buff *buffer, char *basestr, int base)
{
	unsigned long	pow;

	pow = 1;
	while (n / pow >= base)
		pow *= base;
	while (pow)
	{
		write_to_buff(buffer, basestr[(n / pow)]);
		n %= pow;
		pow /= base;
	}
}

int		parse_number(const char *str, size_t *index)
{
	int		i;
	int		neg;
	int		nb;

	neg = 1;
	nb = 0;
	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-')
		neg = -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (ft_isdigit(str[i]))
	{
		if (neg == -1)
			nb = nb * 10 - (str[i] - '0');
		else
			nb = nb * 10 + (str[i] - '0');
		i++;
	}
	*index += i;
	return (nb);
}

long	get_arg_num(va_list ap, t_spec *spec)
{
	long	arg;

	arg = 0;
	if (spec->mod == none)
		arg = va_arg(ap, int);
	else if (spec->mod == hh)
		arg = (char)va_arg(ap, int);
	else if (spec->mod == h)
		arg = (short)va_arg(ap, int);
	else if (spec->mod == l)
		arg = va_arg(ap, long);
	else if (spec->mod == ll)
		arg = va_arg(ap, long long);
	else if (spec->mod == j)
		arg = va_arg(ap, intmax_t);
	else if (spec->mod == j)
		arg = va_arg(ap, size_t);
	return (arg);
}
