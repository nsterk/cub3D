# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: nsterk <nsterk@student.codam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 2020/10/27 11:29:07 by nsterk        #+#    #+#                  #
#    Updated: 2021/05/24 14:07:31 by nsterk        ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME		=	libft.a
HEADER		=	libft.h
REG_FILES 	=	ft_atoi.c ft_bzero.c ft_calloc.c ft_isalpha.c \
				ft_isdigit.c ft_skipspace.c \
				ft_split.c ft_strchr.c ft_strcpy.c ft_strdup.c \
				ft_strlen.c ft_substr.c ft_strtrim.c \
BONUS_FILES =	ft_lstadd_back.c ft_lstclear.c \
				ft_lstdelone.c ft_lstlast.c \
				ft_lstnew.c ft_lstsize.c
REG_OBJS	=	$(REG_FILES:%.c=%.o)
BONUS_OBJS	=	$(BONUS_FILES:%.c=%.o)

CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra
OPTIONS		=	ar rcs
RM			=	rm -f

ifdef WITH_BONUS
OBJ_FILES = $(REG_OBJS) ${BONUS_OBJS}
else
OBJ_FILES = $(REG_OBJS)
endif

all:		$(NAME)

$(NAME):	$(OBJ_FILES)
		$(OPTIONS) $(NAME) $(OBJ_FILES)

%.o: %.c	$(HEADER)
		$(CC) -c $(CFLAGS) -o $@ $<

bonus:
		$(MAKE) WITH_BONUS=1 all

clean:
		$(RM) $(REG_OBJS) ${BONUS_OBJS}

fclean: clean
		$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus %.o
