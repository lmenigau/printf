#* ************************************************************************** *#
#*                                                                            *#
#*                                                        :::      ::::::::   *#
#*   Makefile                                           :+:      :+:    :+:   *#
#*                                                    +:+ +:+         +:+     *#
#*   By: lmenigau <lmenigau@student.42.fr>          +#+  +:+       +#+        *#
#*                                                +#+#+#+#+#+   +#+           *#
#*   Created: 2016/11/18 02:18:30 by lmenigau          #+#    #+#             *#
#*   Updated: 2017/04/13 02:39:51 by lmenigau         ###   ########.fr       *#
#*                                                                            *#
#* ************************************************************************** *#

NAME	= libftprintf.a
SRC		= ft_printf.c utils.c number.c print.c process_format.c wctoutf8.c\
		  ft_lib.c
OBJ		= $(SRC:.c=.o)
CFLAGS	= -Wall -Wextra -Werror
LFLAGS	= -lftprintf
LDFLAGS	= -L.

.PHONY	:	all clean fclean re lib test test_ftprintf

all		:	$(NAME)

$(NAME)	:	$(OBJ)
			$(AR) rcs $(NAME) $?

clean	:
			$(RM) $(OBJ)

fclean	:	clean
			$(RM) $(NAME)


re		:	fclean all

test	:	$(NAME) test_ftprintf
			./test_ftprintf

test_ftprintf: test.c
			$(CC) $(CFLAGS) $(LFLAGS) $(LDFLAGS) -o test_ftprintf test.c

