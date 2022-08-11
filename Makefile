# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pingpanu <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/11 15:12:33 by pingpanu          #+#    #+#              #
#    Updated: 2022/08/11 15:32:48 by pingpanu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CC = gcc

FLAGS = -Wall -Wextra -Werror

SRC = mandatory.c \
      pipex.c \
      utils.c \

HDIR = include

LIB = libft

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME) : $(OBJ)
	@ make -C $(LIB) 
	@ $(CC) $(FLAGS) $(OBJ) -I $(HDIR) -L $(LIB) -lft -o $(NAME)

%.o : %.c
	@ $(CC) $(FLAGS) -c $(SRC) -I $(HDIR)

clean :
	rm -f $(OBJ) 

fclean : clean
	make fclean -C $(LIB)
	rm -f $(NAME)

re: fclean all

.PHONY : all clean fclean re
