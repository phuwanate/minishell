
NAME = minishell

FLAGS = -Wall -Wextra -Werror -fsanitize=address -g

LIBFT = $(LIBFT_DIRECTORY)libft.a
LIBFT_DIRECTORY = ./libft/

SRC = executor.c input_error.c make_everything.c utils.c \
		input_output.c get_next_line_bonus.c get_next_line_utils_bonus.c

OBJS = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	gcc $(FLAGS) $(OBJS) $(LIBFT) -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIRECTORY)

clean:
	$(MAKE) -C $(LIBFT_DIRECTORY) clean
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(LIBFT)
	rm -rf $(NAME)

re: fclean all