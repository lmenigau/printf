/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmenigau <lmenigau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/18 03:27:42 by lmenigau          #+#    #+#             */
/*   Updated: 2017/04/13 01:57:12 by lmenigau         ###   ########.fr       */
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

int		put_wstr_buff(t_buff *buff, wchar_t *str, size_t len)
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

void	write_to_buff(t_buff *buffer, char c)
{
	buffer->buff[buffer->count % BUFF_SIZE] = c;
	buffer->count++;
	if ((buffer->count % BUFF_SIZE) == 0)
		write(1, buffer->buff, BUFF_SIZE);
}

size_t	ft_strchri(const char *str, int c)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != c)
	{
		i++;
	}
	return (i);
}
