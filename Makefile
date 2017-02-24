#* ************************************************************************** *#
#*                                                                            *#
#*                                                        :::      ::::::::   *#
#*   Makefile                                           :+:      :+:    :+:   *#
#*                                                    +:+ +:+         +:+     *#
#*   By: lmenigau <lmenigau@student.42.fr>          +#+  +:+       +#+        *#
#*                                                +#+#+#+#+#+   +#+           *#
#*   Created: 2016/11/18 02:18:30 by lmenigau          #+#    #+#             *#
#*   Updated: 2017/02/23 04:34:09 by lmenigau         ###   ########.fr       *#
#*                                                                            *#
#* ************************************************************************** *#

NAME	= libftprintf.a
SRC		= ft_printf.c get_arg.c
OBJ		= $(SRC:.c=.o)
CFLAGS	= -Wall -Wextra -Ilibft/
LFLAGS	= -lft -lftprintf
LDFLAGS	= -Llibft/ -L.
LIBDIR	= libft/
LIB		:= $(LIBDIR)/libft.a

.PHONY	:	all clean fclean re lib test

test	:	$(NAME) test_ftprintf
			./test_ftprintf

all		:	$(NAME)

$(NAME)	:	$(OBJ) $(LIB)
			$(AR) rcs $(NAME) $?


test_ftprintf: test.c
			$(CC) $(CFLAGS) $(LFLAGS) $(LDFLAGS) -o test_ftprintf test.c

$(LIB)	:	$(LIBDIR)
			$(MAKE) -C $(LIBDIR)

clean	:
			$(RM) $(OBJ)
			$(MAKE) -C $(LIBDIR) fclean

fclean	:	clean
			$(RM) $(NAME)

re		:	fclean all
