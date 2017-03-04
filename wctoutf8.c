/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wctoutf8.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmenigau <lmenigau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 18:47:40 by lmenigau          #+#    #+#             */
/*   Updated: 2017/03/04 09:41:11 by lmenigau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <locale.h>

int		wctoutf8(char *s, wchar_t wchar)
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
	printf("   %hhX, ", out[3]);
	printf("   %hhX, ", out[2]);
	printf("   %hhX, ", out[1]);
	printf("   %hhX\n", out[0]);
	while (i >= 0)
	{
		write(1, &out[i], 1);
		i--;
	}
	return(0);
}

int	main()
{
	setlocale(LC_CTYPE, "");
	wctoutf8("", 0x20AC);
	wctoutf8("", 0x0B4C);
	wctoutf8("", 0x265E);
	wctoutf8("", 0x0800);
	wctoutf8("", 0x1D11E);
	wctoutf8("", 0xE0000);
	printf("%C\n", 0x0B4C);
}
