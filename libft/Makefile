# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kbedene <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/07 13:50:54 by kbedene           #+#    #+#              #
#    Updated: 2018/06/25 13:42:34 by tduverge    ###    #+. /#+    ###.fr      #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC =\
	ft_atoi ft_bzero ft_isalnum ft_isalpha ft_isascii ft_isdigit ft_islower\
	ft_isprint ft_isupper ft_itoa ft_lstadd ft_lstdel ft_lstdelone ft_lstiter\
	ft_lstmap ft_lstnew ft_memalloc ft_memccpy ft_memchr ft_memcmp ft_memcpy\
	ft_memdel ft_memmove ft_memset ft_putchar ft_putchar_fd ft_putendl\
	ft_putendl_fd ft_putnbr ft_putnbr_fd ft_putstr ft_putstr_fd ft_strcat\
	ft_strchr ft_strclr ft_strcmp ft_strcpy ft_strdel ft_strdup ft_strequ\
	ft_striter ft_striteri ft_strjoin ft_strlcat ft_strlen ft_strmap ft_strmapi\
	ft_strncat ft_strncmp ft_strncpy ft_strnequ ft_strnew ft_strnstr ft_strrchr\
	ft_strrev ft_strsplit ft_strstr ft_strsub ft_strtolower ft_strtoupper\
	ft_strtrim ft_swap ft_tolower ft_toupper ft_lstpush ft_lstlen ft_del\
	ft_bubble_sort ft_merge_sort ft_strnjoin ft_lstprint_nb\
	get_next_line ft_atol ft_pow ft_strisdigit ft_strndup

SRC_PRINTF = fd_printf\
		   ft_printf flags\
		   pf_litoa_base pf_luitoa_base\
		   pf_applyflags_nb pf_applyflags_str pf_applyflags_x\
		   pf_applyflags_o\
		   pf_special pf_str pf_d pf_s pf_u pf_c pf_p\
		   pf_upper_c pf_upper_s pf_base pf_percent pf_unicode

SRCS = $(addprefix libft_files/, $(addsuffix .c, $(SRC)))\
	   $(addprefix printf/, $(addsuffix .c, $(SRC_PRINTF)))

LIB_OBJ = $(addprefix libft_files/, $(addsuffix .o, $(SRC)))

PRINTF_OBJ = $(addprefix printf/, $(addsuffix .o, $(SRC_PRINTF)))

CC = gcc

FLAGS = -Wall -Wextra -Werror

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(LIB_OBJ) $(PRINTF_OBJ)
	@ar rcs $(NAME) $(LIB_OBJ) $(PRINTF_OBJ)
	@echo "\033[32mLibft created.\033[0m"

./libft_files/%.o: ./libft_files/%.c
	@$(CC) $(FLAGS) -c $< -o $@

./printf/%.o: ./printf/%.c
	@$(CC) $(FLAGS) -c $< -o $@

clean:
	@/bin/rm -f $(LIB_OBJ) $(PRINTF_OBJ)
	@echo "\033[31mLibft objects deleted.\033[0m"

fclean: clean
	@/bin/rm -f $(NAME)
	@echo "\033[31mLibft binary deleted.\033[0m"

re: fclean all
