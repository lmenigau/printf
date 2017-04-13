/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmenigau <lmenigau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 02:45:06 by lmenigau          #+#    #+#             */
/*   Updated: 2017/04/13 04:11:31 by lmenigau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

const t_spec	g_spec[] = {{BLOW, s, none, 0, 0, 0, {0}, 2},
	{BLOW, S, none, 0, 0, 0, {0}, 2},
	{BLOW, p, l, 0, 0, 0, {1}, 16},
	{BLOW, d, none, 0, 0, 1, {0}, 10},
	{BLOW, D, l, 0, 0, 1, {0}, 10},
	{BLOW, i, none, 0, 0, 1, {0}, 10},
	{BLOW, o, none, 0, 0, 0, {0}, 8},
	{BLOW, O, l, 0, 0, 0, {0}, 8},
	{BLOW, u, none, 0, 0, 0, {0}, 10},
	{BLOW, U, l, 0, 0, 0, {0}, 10},
	{BLOW, x, none, 0, 0, 0, {0}, 16},
	{BUPP, X, none, 0, 0, 0, {0}, 16},
	{BLOW, c, none, 0, 0, 0, {0}, 2},
	{BLOW, C, none, 0, 0, 0, {0}, 2},
	{BLOW, nil, none, 0, 0, 0, {0}, 2}};

long			get_arg(va_list ap, t_spec *spec)
{
	long arg;

	if (spec->conv == c)
		arg = va_arg(ap, int);
	else if (spec->conv == C)
		arg = va_arg(ap, wint_t);
	else if (spec->conv == s || spec->conv == S)
		arg = (long)va_arg(ap, void *);
	else
		return (get_arg_num(ap, spec));
	return (arg);
}

void			parse_mod(t_spec *spec, t_modif mod)
{
	if (spec->mod == none)
		spec->mod = mod;
	else if (spec->mod == h && mod == h)
		spec->mod = hh;
	else if (spec->mod == l && mod == l)
		spec->mod = ll;
}

int				parse_spec(const char *format, va_list ap, t_buff *buff,
		t_conv conv)
{
	t_spec	spec;
	size_t	i;
	size_t	found;

	spec = g_spec[conv];
	i = -1;
	while (format[++i])
	{
		if ((found = ft_strchri("#0-+ ", format[i])) < 5)
			spec.flags[found] = 1;
		else if ((format[i] >= '1' && format[i] <= '9') || format[i] == '*')
			spec.width = parse_number(&format[i], &i, ap);
		else if (format[i] == '.')
		{
			spec.prec = parse_number(&format[++i], &i, ap);
			spec.flags[dot] = 1;
		}
		else if ((found = ft_strchri("__hl_jz", format[i])) < 7)
			parse_mod(&spec, found);
		else
			break ;
	}
	return (process_format(ap, buff, &spec, format[i]));
}

int				match_conv(const char *format, t_conv *conv)
{
	size_t	i;

	i = 0;
	while (format[i] && (ft_strchri("#0-+ .hljz0123456789*", format[i]) < 21))
	{
		i++;
	}
	*conv = ft_strchri("sSpdDioOuUxXcC", format[i]);
	if (format[i] == '\0')
		return (i);
	else
		return (i + 1);
}

int				ft_printf(const char *restrict format, ...)
{
	va_list	ap;
	size_t	i;
	size_t	off;
	t_conv	conv;
	t_buff	buffer;

	i = 0;
	buffer.count = 0;
	va_start(ap, format);
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1] != '\0')
		{
			off = match_conv(&format[i + 1], &conv);
			if (parse_spec(&format[i + 1], ap, &buffer, conv) == -1)
				return (-1);
			i += off;
		}
		else if (format[i] != '%')
			write_to_buff(&buffer, format[i]);
		i++;
	}
	va_end(ap);
	write(1, &buffer.buff, buffer.count % BUFF_SIZE);
	return (buffer.count);
}
