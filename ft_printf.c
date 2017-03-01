/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmenigau <lmenigau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 02:45:06 by lmenigau          #+#    #+#             */
/*   Updated: 2017/02/27 23:57:22 by lmenigau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbr_base_signed(long n, t_buff *buffer)
{
	int		pow;
	int		neg;

	pow = 1;
	neg = 1;
	while (n / pow >= 10 || n / pow <= -10)
		pow *= 10;
	if (n < 0)
	{
		ft_putchar('-');
		neg = -1;
	}
	while (pow)
	{
		ft_putchar((neg * (n / pow)) + '0');
		n %= pow;
		pow /= 10;
	}
}

char	*ft_itoabaseunsigned(char *base, char *buff, long n)
{
	int		pow;
	int		len;
	char	*str;

	len = 1;
	pow = n;
	while (pow /= 10)
		len++;
	if (n < 0)
		len++;
	else
		n = -n;
	if ((str = malloc(len + 1)) == NULL)
		return (NULL);
	str[len--] = '\0';
	while (len >= 0)
	{
		str[len] = -(n % 10) + '0';
		n /= 10;
		if (n == 0 && len == 1)
			str[--len] = '-';
		len--;
	}
	return (str);
}
char	*ft_itoabasesigned(char *base, char *buff, long n)
{
	int		pow;
	int		len;
	char	*str;

	len = 1;
	pow = n;
	while (pow /= 10)
		len++;
	if (n < 0)
		len++;
	else
		n = -n;
	if ((str = malloc(len + 1)) == NULL)
		return (NULL);
	str[len--] = '\0';
	while (len >= 0)
	{
		str[len] = -(n % 10) + '0';
		n /= 10;
		if (n == 0 && len == 1)
			str[--len] = '-';
		len--;
	}
	return (str);
}


const t_spec	g_spec[] = {{BLOW, s, none, 0, 0, 0, {}, 0},
							{BLOW, S, none, 0, 0, 0, {}, 0},
							{BLOW, p, none, 0, 0, 0, {1}, 16},
							{BLOW, d, none, 0, 0, 0, {}, 10},
							{BLOW, D, none, 0, 0, 0, {}, 10},
							{BLOW, i, none, 0, 0, 0, {}, 10},
							{BLOW, o, none, 0, 0, 0, {}, 8},
							{BLOW, O, none, 0, 0, 0, {}, 8},
							{BLOW, u, none, 0, 0, 0, {}, 10},
							{BLOW, U, none, 0, 0, 0, {}, 10},
							{BLOW, x, none, 0, 0, 0, {}, 16},
							{BUPP, X, none, 0, 0, 0, {}, 16},
							{BLOW, c, none, 0, 0, 0, {}, 0},
							{BLOW, C, none, 0, 0, 0, {}, 0}};


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

size_t	parse_spec(const char *format, va_list ap, t_buff *buff)
{
	t_spec	spec;
	size_t i;
	size_t found;

	i = -1;
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
		else if ((found = ft_strchri("hljz", format[i])) < 4)
			spec.mod = parse_mod();
		else
			break;
	}
	get_arg();
	print_arg();
	return (i);
}

int	 ft_printf(const char *restrict format, ...)
{
	va_list	ap;
	size_t	i;
	size_t	j;
	char	*found;
	t_buff	buffer;

	i = 0;
	buffer.count = 0;
	va_start(ap, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			j = i;
			while (format[++j] && format[j] != '%' &&
					ft_strchri("sSpdDioOuUxXcC", format[j]) >= 14)
				parse_spec(&format[i + 1], ap, &buffer);
		}
		buffer.buff[buffer.count++] = format[i];
		i++;
	}
	va_end(ap);
	write(1, &buffer.buff, buffer.count % BUFF_SIZE);
	return (buffer.count);
}
