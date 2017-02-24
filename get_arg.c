/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmenigau <lmenigau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 04:25:27 by lmenigau          #+#    #+#             */
/*   Updated: 2017/02/23 07:41:14 by lmenigau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
sSpdDioOuUxXcC;

void	handle_s(t_spec *spec)
{
}

void	handle_c(t_spec *spec)
{
}

void	handle_C(t_spec *spec)
{
}
void	handle_S(t_spec *spec)
{
}

void	handle_p(t_spec *spec)
{
}

void	handle_d(t_spec *spec)
{
	spec->sign = 1;
	spec->base = 10;
}

void	handle_D(t_spec *spec)
{
	spec->sign = 1;
	spec->base = 10;
}

void	handle_o(t_spec *spec)
{
	spec->base = 8;
}

void	handle_O(t_spec *spec)
{
	spec->base = 8;
}

void	handle_u(t_spec *spec)
{
	spec->base = 10;
}

void	handle_U(t_spec *spec)
{
	spec->base = 10;
}

void	handle_x(t_spec *spec)
{
	spec->base = 16;
}

void	handle_X(t_spec *spec)
{
	spec->base = 16;
	spec->basestr = "0123456789ABCDEF";
}
