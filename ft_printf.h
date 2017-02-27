/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmenigau <lmenigau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 02:49:51 by lmenigau          #+#    #+#             */
/*   Updated: 2017/02/27 09:59:32 by lmenigau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include "libft.h"

# define BLOW	"0123456789abcdef"
# define BUPP	"0123456789ABCDEF"

# define BUFF_SIZE	512

int	 ft_printf(const char *restrict format, ...);

typedef enum	e_modif
{
	none,
	hh,
	h,
	l,
	ll,
	j,
	z,
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

static const char *flags= "#0-+ ";
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

typedef struct	s_buff
{
	char	buff[BUFF_SIZE];
	size_t	count;
}				t_buff;

long	get_int(va_list ap);
long	get_long(va_list ap);
#endif
