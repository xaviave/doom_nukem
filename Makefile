# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: flombard <flombard@student.le-101.fr>      +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2018/10/15 13:25:38 by xamartin     #+#   ##    ##    #+#        #
#    Updated: 2019/01/08 16:07:18 by flombard    ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

.PHONY: all clean fclean re

#COMPILATION

CC = gcc
RM = rm -f
NAME = doom_nukem
LIBFT = libft/
INC = includes/doom.h
CFLAGS = -Wall -Wextra -Werror -I includes -F ./Frameworks -O2
SDLFLAGS =  -rpath ./Frameworks -F ./Frameworks  -framework SDL2 \
			-framework SDL2_image \
			-framework SDL2_mixer \
			-framework SDL2_ttf


#PATH

SRCS_PATH = ./srcs/
OBJS_PATH = ./srcs/

FILES = main.c \
		parser/parse_map.c \
		parser/parse_vertex.c \
		parser/parse_sector.c \
		parser/parse_to_level.c \
		tools/error_parsing.c \
		tools/check_int.c \
		tools/list.c \
		tools/create_vertex.c \
		tools/list_len.c \
		render/init_free_renderer.c \
		render/render_map.c
		#main_sdl.c\
		event.c\


SRCS = $(addprefix $(SRCS_PATH), $(FILES))
OBJS = $(addprefix $(OBJS_PATH), $(FILES:.c=.o))


#RULES

all: $(NAME)

$(NAME): $(OBJS)
	make -C $(LIBFT)
	$(CC) $(CFLAGS) $(LIB_FLAG) -o $@ $(OBJS) $(SDLFLAGS)  $(CFLAGS) -L $(LIBFT) -lft


$(OBJS_PATH)%.o: $(SRCS_PATH)%.c $(INC)
	$(CC) $(CFLAGS) -o $@ -c $<


clean:
	@make -C $(LIBFT) clean
	@rm -f $(OBJS)

fclean: clean
	@rm -f libft/libft.a
	@rm -f $(NAME)

re: fclean all
