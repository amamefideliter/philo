# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dzubkova <dzubkova@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/28 13:40:29 by dzubkova          #+#    #+#              #
#    Updated: 2024/09/24 13:41:35 by dzubkova         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FILES = sources/philos_utils.c sources/critical_session.c sources/monitor.c sources/philo_eat.c sources/simulation.c main.c
OFILES = $(FILES:.c=.o)
HFILES = includes/philos.h

NAME = philo

CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OFILES) $(HFILES)
	make bonus -C ./libft
	cc $(CFLAGS) $(OFILES) libft/libft.a -o $(NAME)

%.o: %.c
	cc -c $(CFLAGS) $< -o $@

clean:
	make clean -C ./libft
	rm -f $(OFILES)

fclean: clean
	make fclean -C ./libft
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean all re