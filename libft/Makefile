# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: awerebea <awerebea@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/04/30 21:56:47 by awerebea          #+#    #+#              #
#    Updated: 2020/05/24 14:30:59 by awerebea         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME     = libft.a
CC       = gcc
CFLAGS   = -Wall -Wextra -Werror
INCLDIR  = ./includes
SRCDIR   = ./src
FLSDIR_1 = print
FLS_1    = $(addprefix $(FLSDIR_1)/, \
			ft_putchar_fd \
			ft_putendl_fd \
			ft_putnbr_fd \
			ft_putstr_fd)
FLSDIR_2 = strings
FLS_2    = $(addprefix $(FLSDIR_2)/, \
			ft_strchr \
			ft_strdup \
			ft_strlcat \
			ft_strlcpy \
			ft_strlen \
			ft_strncmp \
			ft_strnstr \
			ft_strrchr \
			ft_split \
			ft_strjoin \
			ft_strmapi \
			ft_strtrim \
			ft_substr)
FLSDIR_3 = memory
FLS_3    = $(addprefix $(FLSDIR_3)/, \
			ft_bzero \
			ft_calloc \
			ft_memccpy \
			ft_memchr \
			ft_memcmp \
			ft_memcpy \
			ft_memmove \
			ft_memset)
FLSDIR_4 = symbols
FLS_4    = $(addprefix $(FLSDIR_4)/, \
			ft_isalnum \
			ft_isalpha \
			ft_isascii \
			ft_isdigit \
			ft_isprint \
			ft_tolower \
			ft_toupper)
FLSDIR_5 = numbers
FLS_5    = $(addprefix $(FLSDIR_5)/, \
			ft_atoi \
			ft_itoa)
FLSDIR_6 = lists
FLS_6    = $(addprefix $(FLSDIR_6)/, \
			ft_lstadd_back \
			ft_lstadd_front \
			ft_lstclear \
			ft_lstdelone \
			ft_lstiter \
			ft_lstlast \
			ft_lstmap \
			ft_lstnew \
			ft_lstsize)
SRC      = $(FLS_1) $(FLS_2) $(FLS_3) $(FLS_4) \
			$(FLS_5) $(FLS_6)
OBJDIR   = ./obj
OBJ      = $(addprefix $(OBJDIR)/, $(SRC:=.o))

.PHONY: all clean fclean

all:			$(NAME)

$(NAME):		$(OBJDIR) $(OBJ)
	@echo Linking $(NAME)
	@ar rcs		$(NAME) $(OBJ)
	@ranlib		$(NAME)

$(OBJDIR):
	@echo Creating $(NAME) objects directories
	@mkdir -p	$(OBJDIR)
	@mkdir -p	$(addprefix $(OBJDIR)/, $(FLSDIR_1) $(FLSDIR_2) $(FLSDIR_3) \
				$(FLSDIR_4) $(FLSDIR_5) $(FLSDIR_6))

$(OBJ):			$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@echo Compiling $<
	@$(CC)		$(CFLAGS) -c $< -I$(INCLDIR) -o $@

clean:
	@echo Cleaning $(NAME) objects directory
	@rm -rf		$(OBJDIR)

fclean:			clean
	@echo Removing $(NAME)
	@rm -f		$(NAME)

re:				fclean all
