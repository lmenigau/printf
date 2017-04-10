/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wctoutf8.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmenigau <lmenigau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 18:47:40 by lmenigau          #+#    #+#             */
/*   Updated: 2017/04/10 18:55:19 by lmenigau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <locale.h>

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
	return(0);
}

//int	main()
//{
//	setlocale(LC_CTYPE, "");
//	wctoutf8("", 0x20AC);
//	wctoutf8("", 0x0B4C);
//	wctoutf8("", 0x265E);
//	wctoutf8("", 0x0800);
//	wctoutf8("", 0x1D11E);
//	wctoutf8("", 0xE0000);
//	printf("%C\n", 0x0B4C);
//}
