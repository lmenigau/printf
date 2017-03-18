/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmenigau <lmenigau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 02:45:06 by lmenigau          #+#    #+#             */
/*   Updated: 2017/03/18 03:32:29 by lmenigau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"


const t_spec	g_spec[] = {{BLOW, s, none, 0, 0, 0, {0}, 0},
							{BLOW, S, none, 0, 0, 0, {0}, 0},
							{BLOW, p, none, 0, 0, 0, {1}, 16},
							{BLOW, d, none, 0, 0, 0, {0}, 10},
							{BLOW, D, l, 0, 0, 0, {0}, 10},
							{BLOW, i, none, 0, 0, 0, {0}, 10},
							{BLOW, o, none, 0, 0, 0, {0}, 8},
							{BLOW, O, l, 0, 0, 0, {0}, 8},
							{BLOW, u, none, 0, 0, 0, {0}, 10},
							{BLOW, U, l, 0, 0, 0, {0}, 10},
							{BLOW, x, none, 0, 0, 0, {0}, 16},
							{BUPP, X, none, 0, 0, 0, {0}, 16},
							{BLOW, c, none, 0, 0, 0, {0}, 0},
							{BLOW, C, none, 0, 0, 0, {0}, 0}};

long	get_arg(va_list ap, t_buff *buff, t_spec *spec)
{
	long arg;

	if (spec->conv == c)
		arg = va_arg(ap, int);
	else if (spec->conv == C)
		arg = va_arg(ap, wint_t);
	else if (spec->conv == s || spec->conv == S)
		arg = (long)va_arg(ap, void *);
	else
		return (get_arg_num(ap, buff, spec));
	return (arg);
}

void	 parse_mod(t_spec *spec, t_modif mod)
{
	if (spec->mod == none)
		spec->mod = mod;
	else if (spec->mod == h && mod == h)
		spec->mod = hh;
	else if (spec->mod == l && mod == l)
		spec->mod = ll;
}

int		parse_spec(const char *format, va_list ap, t_buff *buff, size_t found)
{
	t_spec	spec;
	size_t i;
	long	arg;

	i = -1;
	arg = 0;
	spec = g_spec[found];
	i = -1;
	while (format[++i] && format[i] != '%')
	{
		if ((found = ft_strchri("#0-+ ", format[i])) < 5)
			spec.flags[found] = 1;
		else if (format[i] >= '1' && format[i] <= '9')
			spec.width = ft_atoi(&format[i]);
		else if (format[i] == '.')
			spec.prec = parse_number(&format[i + 1], &i);
		else if ((found = ft_strchri("__hl_jz", format[i])) < 4)
			parse_mod(&spec, found);
		else
			break;
	}
	printf("mod:%d\n", spec.mod);
	arg = get_arg(ap, buff, &spec);
	printf("%ld\n", arg);
	print_arg(arg, &spec, buff);
	return (0);
}

int	 ft_printf(const char *restrict format, ...)
{
	va_list	ap;
	size_t	i;
	size_t	j;
	size_t 	found;
	t_buff	buffer;

	i = 0;
	buffer.count = 0;
	va_start(ap, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			j = i;
			while (format[++j] && format[j] != '%')
			{
				found = ft_strchri("sSpdDioOuUxXcC", format[j]);
				if (found <= 13)
				{
					parse_spec(&format[i + 1], ap, &buffer, found);
					i = j + 1;
				}
			}
			i++;
		}
		buffer.buff[buffer.count++] = format[i];
		i++;
	}
	return (buffer.count);
}
