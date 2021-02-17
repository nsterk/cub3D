# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: nsterk <nsterk@student.codam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 2020/10/27 11:29:07 by nsterk        #+#    #+#                  #
#    Updated: 2021/02/17 14:21:42 by nsterk        ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME		=	cub3d
CC			=	gcc
W_FLAGS		=	-Wall -Werror -Wextra -std=c89
MLX_FLAGS	=	-framework OpenGL -framework Appkit -Imlx -Iinc -fsanitize=address -g

# MLX_PATH	=	./mlx/
GNL_PATH	=	./srcs/gnl/
# LIBFT_PATH	=	./srcs/libft/

GNL_C	=	get_next_line.c get_next_line_utils.c
# LIBFT_SRCS	=	

GNL_SRCS	=	$(GNL_C:%=$(GNL_PATH)%)

# place main.c in srcs folder
SRCS		=	main.c \
				$(GNL_SRCS)

OBJS		=	$(SRCS:.c=.o)

all: $(NAME)

$(NAME):
	# make -C ./mlx
	# cp ./mlx/libmlx.dylib .
	$(CC) $(W_FLAGS) $(MLX_FLAGS) $(SRCS) libmlx.dylib -o $(NAME)

clean:
	# make clean -C ./mlx
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re:	fclean all

.PHONY: all clean
