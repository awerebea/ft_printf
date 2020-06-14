# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: awerebea <awerebea@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/21 14:51:15 by awerebea          #+#    #+#              #
#    Updated: 2020/06/14 16:59:05 by awerebea         ###   ########.fr        #
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
			ft_printf_print_c \
			ft_printf_print_d_i \
			ft_printf_print_f \
			ft_printf_print_p_u_x_o \
			ft_printf_print_s \
			ft_printf_utils \
			ft_printf_utils2

OBJ      = $(addprefix $(OBJDIR), $(SRC:=.o))
DFLS     = $(SRC:=.d)

override FLAGS ?= $(CFLAGS)

include $(wildcard $(addprefix $(OBJDIR), $(DFLS)))

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

bonus: all

clean:
	rm -rf		$(OBJDIR)

fclean:			clean
	rm -f		$(NAME)

re:				fclean all

.PHONY: all clean fclean re debug bonus
