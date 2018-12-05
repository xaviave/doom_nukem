.PHONY = all, clean, fclean, re


#COMPILATION

CC = gcc
NAME = doom_nukem
INC = -I includes/
CFLAGS = -Wall -Werror -Wextra


#PATH

SCRS_PATH = ./srcs/
OBJS_PATH = ./srcs/
FILES = \ 

SRCS = $(addprefix $(SRCS_PATH), $(FILES))
OBJS = $(addprefix $(OBJS_PATH), $(FILES:.c=.o))


#RULES

all: $(NAME)


$(NAME): $(OBJS)
	@$(CC) -g $(CFLAGS) $(INC) -o $@ $(OBJS)

$(OBJS_PATH)%.o: $(SRCS_PATH)%.c
	@$(CC) $(CFLAGS) $(INC) -o $@ -c $<


clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all
