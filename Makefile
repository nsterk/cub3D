# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: nsterk <nsterk@student.codam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 2020/10/27 11:29:07 by nsterk        #+#    #+#                  #
#    Updated: 2021/05/23 18:00:51 by nsterk        ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

# put back  -Wall -Wextra -Werror  flags
# remove -fsanitize=address -g flags

NAME		=	cub3D
CC			=	gcc
W_FLAGS		=	-Wall -Wextra -Werror -Wunused-variable -Wunused-value -Wunused-function -std=c89 -Iinc
MLX_FLAGS	=	-framework OpenGL -framework Appkit -Imlx -g # -fsanitize=address

# MLX_PATH	=	./mlx/
LIBFT_PATH	=	./srcs/libft/
GNL_PATH	=	./srcs/gnl/
INIT_PATH	=	./srcs/init/
EXTRA_PATH	=	./srcs/extra/
PARSE_PATH	=	./srcs/parsing/
RAYCST_PATH	=	./srcs/raycasting/
CUB3D_PATH	=	./srcs/

LIBFT_C		=	ft_atoi.c ft_bzero.c ft_calloc.c \
				ft_free_array.c \
				ft_isalnum.c ft_isalpha.c ft_isdigit.c \
				ft_lstnew.c ft_lstlast.c ft_lstsize.c \
				ft_lstdelone.c ft_lstclear.c \
				ft_stradd_back.c \
				ft_skipspace.c ft_strcmp.c \
				ft_strchr.c ft_strcpy.c ft_strlcpy.c \
				ft_strdup.c ft_strcdup.c ft_strccpy.c \
				ft_strlen.c ft_strclen.c ft_substr.c \
				ft_strtrim.c ft_split.c
GNL_C		=	get_next_line.c get_next_line_utils.c
INIT_C		=	complete_data.c init_01.c init_02.c
EXTRA_C		=	bmp.c draw.c colours.c keys.c utils.c \
				free_alloc.c exit.c
PARSE_C		=	parser.c parse_map_01.c parse_map_02.c \
				parse_colour_res.c \
				parse_tex.c validate_map.c utils.c
RAYCST_C	=	move.c rotate.c raycaster.c \
				textures.c sprites.c \
				window_loop.c
CUB3D_C		=	main.c

LIBFT_SRCS	=	$(LIBFT_C:%=$(LIBFT_PATH)%)
GNL_SRCS	=	$(GNL_C:%=$(GNL_PATH)%)
INIT_SRCS	=	$(INIT_C:%=$(INIT_PATH)%)
EXTRA_SRCS	=	$(EXTRA_C:%=$(EXTRA_PATH)%)
PARSE_SRCS	=	$(PARSE_C:%=$(PARSE_PATH)%)
RAYCST_SRCS	=	$(RAYCST_C:%=$(RAYCST_PATH)%)
CUB3D_SRCS	=	$(CUB3D_C:%=$(CUB3D_PATH)%)

SRCS		= 	$(LIBFT_SRCS) $(GNL_SRCS) \
				$(INIT_SRCS) $(EXTRA_SRCS) \
				$(PARSE_SRCS) \
				$(RAYCST_SRCS) $(CUB3D_SRCS)
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

.PHONY: all clean fclean re
