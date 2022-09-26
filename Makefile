# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mzridi <mzridi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/13 21:35:46 by mzridi            #+#    #+#              #
#    Updated: 2022/09/26 10:13:25 by mzridi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc

SRC = main.c ft_atoi.c constructer.c utils.c

OBJ = $(SRC:.c=.o) 


all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -g -o $(NAME)


%.o: %.c philo.h
	$(CC) -Wall -Wextra -Werror -pthread -c $< -o $@

clean :
	@rm -rf $(OBJ)  

fclean : clean
	@rm -rf $(NAME) philo 

re : fclean all