/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wctoutf8.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmenigau <lmenigau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 18:47:40 by lmenigau          #+#    #+#             */
/*   Updated: 2017/02/24 21:16:17 by lmenigau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <locale.h>

int		wctoutf8(char *s, wchar_t wchar)
{
	int		out;
	int		i;

	i = 0;
	while (wchar)
	{
		out |= (wchar & 0b111111) | 0b10000000;
		wchar >>= 6;
		out <<= 8;
		i++;
	}
	out |= ~0 << (8 - i);
	out <<= (1 * 8);
	out = 0xAC82E2;
	write(1, &out, 3);
	return (i);
}

int	main()
{
	setlocale(LC_CTYPE, "");
	wctoutf8("", 0x20AC);
	//printf("%C\n", 8364);
}
