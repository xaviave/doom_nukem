# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: lloyet <lloyet@student.le-101.fr>          +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2018/09/20 01:31:31 by lloyet       #+#   ##    ##    #+#        #
#    Updated: 2019/02/17 23:29:04 by lloyet      ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

NAME = DOOM_MAP

# COMPILER#
CC	= clang
CFLAGS = -Wall -Wextra -Werror

# DIR
SRCDIR = ./src/
INCDIR = ./inc/
OBJDIR = ./obj/
LIBDIR = ./lib/

SRC =	main.c \
		misc.c \
		file.c \
		engine.c \
		image.c \
		layer.c \
		layer_utils.c \
		shape.c \
		shape_utils.c \
		vertex.c \
		draw.c \
		draw_utils.c \
		gui.c \
		gui_utils.c \
		framework.c \
		event.c \
		event_utils.c \

OBJ	= $(addprefix $(OBJDIR), $(SRC:.c=.o))

# FT_LIBRARY#
FT = $(addprefix $(LIBDIR), libft)
LIBFT = $(addprefix $(FT), libft.a)
LIBINC = -I $(FT)
LIBLINK	= -L $(FT) -lft

# HOOK_LIBRARY#
HK = $(addprefix $(LIBDIR), libhook)
LIBHK = $(addprefix $(HK), libhk.a)
HKINC = -I $(addprefix $(HK), inc)
HKLINK = -L $(HK) -lhk

# PAYLOAD_LIBRARY#
PL = $(addprefix $(LIBDIR), payload)
LIBPL = $(addprefix $(PL), libpl.a)
PLINC = -I $(addprefix $(PL), inc)
PLLINK = -L $(PL) -lpl

# MINILIBX LIBRARY
MLX = $(addprefix $(LIBDIR), minilibx_macos)
LIBMLX = $(addprefix $(MLX), libmlx.a)
MLXINC = -I $(MLX)
MLXLINK = -L $(MLX) -lmlx -framework OpenGL -framework AppKit

.PHONY: all clean fclean re
.SILENT: $(OBJDIR) fclean clean re
all: $(OBJDIR) $(LIBFT) $(LIBHK) $(LIBPL) $(LIBMLX) $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(OBJ) $(MLXLINK) $(LIBLINK) $(HKLINK) $(PLLINK) -lm -lpthread -o $(NAME)
	@echo "[$(NAME)]: all done."

$(OBJDIR)%.o: $(SRCDIR)%.c
	$(CC) $(CFLAGS) $(LIBINC) $(HKINC) $(PLINC) $(MLXINC) -I $(INCDIR) -c $< -o $@

$(OBJDIR):
	@mkdir -p $@

$(LIBFT):
	make -C $(FT)

$(LIBPL):
	make -C $(PL)

$(LIBHK):
	make -C $(HK)

$(LIBMLX):
	make -C $(MLX)

clean:
	rm -rf $(OBJDIR)
	make clean -C $(FT)
	make clean -C $(HK)
	make clean -C $(PL)
	make clean -C $(MLX)

fclean: clean
	rm -rf $(NAME)
	make fclean -C $(FT)
	make fclean -C $(HK)
	make fclean -C $(PL)

re: fclean all
