# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nkamolba <nkamolba@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/15 19:35:45 by nkamolba          #+#    #+#              #
#    Updated: 2018/12/20 18:40:43 by nkamolba         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls
FLAG = -Wall -Wextra -Werror
LIB = -Llibft -lft
LIBFT = libft/libft.a

FILE = main.c \
		binary_tree.c compare.c \
		parse.c file.c file_data.c max.c \
		process.c process_dir.c process_recursive.c \
		print.c print_mode.c print_l.c \
		free.c utils.c

FILE_O = $(FILE:%.c=%.o)

all : $(LIBFT) $(NAME)

$(LIBFT):
	@make -C libft

$(NAME) : $(FILE_O) | $(LIBFT)
	@gcc $(FLAG) -o $(NAME) $(FILE_O) $(LIB)
	@echo "$(NAME) created"

%.o: %.c
	@gcc $(FLAG) -c $< -o $@

clean:
	@make clean -C libft
	@rm -f $(FILE_O)
	@echo "$(NAME) clean done"

fclean: clean
	@rm -f $(LIBFT)
	@echo "libft.a fclean done"
	@rm -f $(NAME)
	@echo "$(NAME) fclean done"

re: fclean all

.PHONY: all clean fclean re