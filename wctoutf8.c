/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wctoutf8.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmenigau <lmenigau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 18:47:40 by lmenigau          #+#    #+#             */
/*   Updated: 2017/04/11 18:46:08 by lmenigau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <locale.h>

size_t	wchar_len(wchar_t *str)
{
	size_t i;
	size_t count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] <= 0x7F)
			count++;
		else if (str[i] <= 0x07FF)
			count += 2;
		else if (str[i] <= 0xFFFF)
			count += 3;
		else if (str[i] <= 0x10FFFF)
			count += 4;
		i++;
	}
	return (count);
}

int		check_utf8(t_buff *buff, wchar_t wchar)
{
	if (wchar <= 127)
		write_to_buff(buff, wchar);
	else if (MB_CUR_MAX == 4 &&
			(wchar <= 0xD7FF || wchar >= 0xE000 || wchar <= 0x10FFFF))
		wctoutf8(buff, wchar);
	else
		return (-1);
	return (0);
}

int		wctoutf8(t_buff *buff, wchar_t wchar)
{
	char	out[4];
	int		i;

	i = 0;
	while (wchar)
	{
		out[i] = (wchar & 0b111111) | 0b10000000;
		wchar >>= 6;
		i++;
	}
	i--;
	if ((out[i] & 0b01111111) & (~0 << (6 - i)))
	{
		i++;
		out[i] = 0;
	}
	out[i] = out[i] | (~0 << (7 - i));
	while (i >= 0)
	{
		write_to_buff(buff, out[i]);
		i--;
	}
	return (1);
}
