# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: mel-akio <mel-akio@student.le-101.fr>      +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2018/10/15 13:25:38 by xamartin     #+#   ##    ##    #+#        #
#    Updated: 2019/05/09 01:42:43 by mel-akio    ###    #+. /#+    ###.fr      #
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
CFLAGS = -Wall -Wextra -Werror -I includes -F ./Frameworks -O2 -g 
MINILIBX = minilibx_macos/libmlx.a
LIB_FLAG = -framework OpenGl -framework AppKit
SDL_FLAG = -rpath ./Frameworks -F ./Frameworks  -framework SDL2 \
		   -framework SDL2_image \
		   -framework SDL2_mixer \
		   -framework SDL2_ttf

#PATH

SRCS_PATH = ./srcs/
OBJS_PATH = ./srcs/

FILES = main.c \
		parser/parse_map.c \
		parser/parse_vertex.c \
		parser/parse_linedef.c \
		parser/parse_sector.c \
		parser/parse_object_player.c \
		parser/parse_to_level.c \
		parser/p_to_level.c \
		tools/error_parsing.c \
		tools/check_int.c \
		tools/list.c \
		tools/create_vertex.c \
		tools/list_line.c \
		tools/list_len.c \
		tools/list_entity.c \
		tools/history.c \
		tools/hud.c \
		tools/textures_tools.c \
		tools/textures_tools_2.c \
		tools/int_check.c \
		tools/free_mem.c \
		render/error_graph.c \
		render/render_map.c \
		render/render_map_3.c \
		render/event/event.c \
		render/event/ai.c \
		render/wall_infos.c \
		render/event/player.c \
		render/event/event2.c \
		render/math.c \
		render/music.c \
		render/mlx/img.c \
		render/mlx/color.c \
		render/mlx/draw.c \
		render/mlx/draw2.c \
		render/send_infos/sector_infos.c \
		render/send_infos/mob_infos.c \
		render/send_infos/send_coords.c \
		render/send_infos/send_ids.c \
		render/send_infos/send_linedef_coords.c \
		render/send_infos/triangulation_player.c \
		render/render_calculate.c \
		render/render_calculate_2.c \
		render/render_map_2.c \
		render/render_sprites.c \
		render/physics.c \



SRCS = $(addprefix $(SRCS_PATH), $(FILES))
OBJS = $(addprefix $(OBJS_PATH), $(FILES:.c=.o))


#RULES

all: $(NAME)

$(NAME): $(OBJS)
	make -C $(LIBFT)
	make -C minilibx_macos
	$(CC) $(CFLAGS) $(LIB_FLAG) -o $@ $(OBJS) $(MINILIBX) $(SDL_FLAG) $(CFLAGS) -L $(LIBFT) -lft


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
