# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: awerebea <awerebea@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/21 14:51:15 by awerebea          #+#    #+#              #
#    Updated: 2020/05/24 16:06:09 by awerebea         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME     = libftprintf.a
CC       = gcc
CFLAGS   = -Wall -Wextra -Werror
SRC      = ft_printf \
			ft_printf_utils \
			ft_printf_utils2 \
			ft_printf_print_str \
			ft_printf_print_ptr \
			ft_printf_print_ptr_uns_hex \
			ft_printf_print_int \
			ft_printf_print_char \
			ft_printf_parsing
OBJDIR   = ./obj
OBJ      = $(addprefix $(OBJDIR)/, $(SRC:=.o))
LIBFTDIR = ./libft
LIBFTINC = ./includes
LIBFT    = libft.a

.PHONY: all clean fclean cleanall bonus

all:			$(NAME)

$(NAME):		$(OBJDIR) $(OBJ)
	@echo Merging: $(NAME) with $(LIBFT)
	@make -C	$(LIBFTDIR)
	@cp			$(LIBFTDIR)/$(LIBFT) ./$(NAME)
	@ar rcs		$(NAME) $(OBJ)
	@ranlib		$(NAME)

$(OBJDIR):
	@echo Creating $(NAME) objects directories
	@mkdir -p	$(OBJDIR)

$(OBJ):			$(OBJDIR)/%.o: ./%.c
	@echo Compiling $<
	@$(CC)		$(CFLAGS) -c $< -I$(LIBFTDIR)/$(LIBFTINC) -o $@

clean:
	@echo Cleaning $(NAME) objects directory
	@rm -rf		$(OBJDIR)

fclean:			clean
	@echo Removing $(NAME)
	@rm -f		$(NAME)

cleanall:		fclean
	@make -C	$(LIBFTDIR) fclean

re:				fclean all
