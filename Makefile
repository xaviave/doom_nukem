# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: mel-akio <mel-akio@student.le-101.fr>      +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2018/10/15 13:25:38 by xamartin     #+#   ##    ##    #+#        #
#    Updated: 2019/02/19 17:03:19 by mel-akio    ###    #+. /#+    ###.fr      #
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
CFLAGS = -Wall -Wextra -Werror -I includes -O2
MINILIBX = minilibx_macos/libmlx.a
LIB_FLAG = -framework OpenGl -framework AppKit


#PATH

SRCS_PATH = ./srcs/
OBJS_PATH = ./srcs/

FILES = main.c \
		parser/parse_map.c \
		parser/parse_vertex.c \
		parser/parse_linedef.c \
		parser/parse_sector.c \
		parser/parse_to_level.c \
		parser/p_to_level.c \
		parser/info_debug.c \
		tools/error_parsing.c \
		tools/check_int.c \
		tools/list.c \
		tools/create_vertex.c \
		tools/list_line.c \
		tools/list_len.c \
		tools/textures_tools.c \
		render/error_graph.c \
		render/draw.c \
		render/img.c \
		render/color.c \
		render/render_map.c \
		render/event.c \
		render/send_info.c \
		render/math.c \
		


SRCS = $(addprefix $(SRCS_PATH), $(FILES))
OBJS = $(addprefix $(OBJS_PATH), $(FILES:.c=.o))


#RULES

all: $(NAME)

$(NAME): $(OBJS)
	make -C $(LIBFT)
	make -C minilibx_macos
	$(CC) $(CFLAGS) $(LIB_FLAG) -o $@ $(OBJS) $(MINILIBX)  $(CFLAGS) -L $(LIBFT) -lft


$(OBJS_PATH)%.o: $(SRCS_PATH)%.c $(INC)
	$(CC) $(CFLAGS) -o $@ -c $<


clean:
	@make -C $(LIBFT) clean
	@make -C minilibx_macos clean
	@rm -f $(OBJS)

fclean: clean
	@rm -f libft/libft.a
	@rm -f minilibx_macos/libmlx.a
	@rm -f $(NAME)

re: fclean all
