# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mzridi <mzridi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/13 21:35:46 by mzridi            #+#    #+#              #
#    Updated: 2022/09/24 21:11:25 by mzridi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc

SRC = main.c ft_atoi.c constructer.c utils.c
BONUS_SRC = 

OBJ = $(SRC:.c=.o) 

BONUS_OBJ = $(BONUS_SRC:.c=.o) 

all: $(NAME)

bonus: $(BONUS_OBJ)
	$(CC) $(BONUS_OBJ) -o philo_bonus

$(NAME): $(OBJ)
	$(CC) $(OBJ) -g -o $(NAME)


%.o: %.c philo.h
	$(CC) -Wall -Wextra -Werror -pthread -c $< -o $@

clean :
	@rm -rf $(OBJ) $(BONUS_OBJ) 

fclean : clean
	@rm -rf $(NAME) philo philo_bonus

re : fclean all