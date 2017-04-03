/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmenigau <lmenigau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/18 03:27:42 by lmenigau          #+#    #+#             */
/*   Updated: 2017/04/03 20:36:00 by lmenigau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ft_printf.h"

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

