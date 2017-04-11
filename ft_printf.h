/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmenigau <lmenigau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 02:49:51 by lmenigau          #+#    #+#             */
/*   Updated: 2017/04/11 19:04:01 by lmenigau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <wchar.h>
# include "libft.h"

# define BLOW	"0123456789abcdef"
# define BUPP	"0123456789ABCDEF"

# define BUFF_SIZE	(4096 * 16)

int	 ft_printf(const char *restrict format, ...);

typedef enum	e_modif
{
	none,
	hh,
	h,
	l,
	ll,
	j,
	z
}				t_modif;

typedef enum	e_conv
{
	s,
	S,
	p,
	d,
	D,
	i,
	o,
	O,
	u,
	U,
	x,
	X,
	c,
	C,
	nil
}				t_conv;

typedef enum	e_flag
{
	hash,
	zero,
	minus,
	plus,
	space,
	dot
}				t_flag;

typedef union	u_arg
{
	int			none;
	char		hh;
	short		h;
	long		l;
	long long	ll;
	intmax_t	j;
	size_t		z;
}				t_arg;

typedef struct	s_spec
{
	char	*basestr;
	t_conv	conv;
	t_modif	mod;
	int		width;
	int		prec;
	int		sign;
	int		flags[6];
	int		base;
}				t_spec;

typedef struct s_print_info
{
	long	arg;
	int		padlen;
	int		preclen;
	int		arglen;
	char	sign;
	char	padchar;
}				t_print_info;

typedef struct	s_buff
{
	char	buff[BUFF_SIZE];
	size_t	count;
}				t_buff;

long	get_int(va_list ap);
long	get_long(va_list ap);
void	write_to_buff(t_buff *buffer, char c);
long	get_arg_num(va_list ap, t_spec *spec);
int		parse_number(const char *str, size_t *index);
void	ft_putnbr_base_signed(long n, t_buff *buffer, char *basestr, int base);
size_t	ft_strchri(const char *str, int c);
int		numlen(long n, int base);
int		print_arg(t_print_info *print_info, t_spec *spec, t_buff *buffer);
void	ft_putnbr_base_unsigned(unsigned long n, t_buff *buffer, char *basestr, int base);
int		process_format(va_list ap, t_buff *buff, t_spec *spec, char convchar);
long	get_arg(va_list ap, t_spec *spec);
int		wctoutf8(t_buff *buff, wchar_t wchar);
size_t	wchar_len(wchar_t *str);
int		check_utf8(t_buff *buff, wchar_t wchar);

#endif
