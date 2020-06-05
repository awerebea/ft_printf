# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: awerebea <awerebea@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/21 14:51:15 by awerebea          #+#    #+#              #
#    Updated: 2020/06/05 20:15:49 by awerebea         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME     = libftprintf.a
CC       = gcc
CFLAGS   = -Wall -Wextra -Werror
OFLAGS   = -O2
DBGFLAGS = -g
INCLUDES = -I includes/
SRCDIR   = src/
OBJDIR   = obj/

SRC      = ft_printf \
			ft_printf_libft \
			ft_printf_parsing \
			ft_printf_print_char \
			ft_printf_print_int \
			ft_printf_print_ptr_uns_hex \
			ft_printf_print_str \
			ft_printf_utils \
			ft_printf_utils2

			# ft_printf_print_ptr \
			# ft_printf_print_uns_hex \

OBJ      = $(addprefix $(OBJDIR), $(SRC:=.o))
DFLS     = $(SRC:=.d)

override FLAGS ?= $(CFLAGS)

all:			$(OBJDIR) $(NAME)

$(NAME):		$(OBJ)
	ar rc		$(NAME) $?
	ranlib		$(NAME)

$(OBJ):			$(OBJDIR)%.o: $(SRCDIR)%.c
	$(CC)		$(FLAGS) $(INCLUDES) -c $< -o $@ -MD

$(OBJDIR):
	mkdir -p	$(OBJDIR)

debug:
	make FLAGS="$(CFLAGS) $(DBGFLAGS)" re

include $(wildcard $(addprefix $(OBJDIR), $(DFLS)))

clean:
	rm -rf		$(OBJDIR)

fclean:			clean
	rm -f		$(NAME)

re:				fclean all

.PHONY: all clean fclean re
