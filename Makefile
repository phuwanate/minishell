NAME = minishell

FLAGS = -Wall -Wextra -Werror -fsanitize=address -g

LIBFT = $(LIBFT_DIRECTORY)libft.a
LIBFT_DIRECTORY = ./libft/

READLINE = /usr/local/opt/readline

SRC = executor.c input_error.c utils.c\
		input_output.c get_next_line_bonus.c get_next_line_utils_bonus.c\
		handle_memory.c mns.c executor_utils.c
#make_everything.c 
OBJ_DIR = object/

OBJS = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	gcc $(FLAGS) -I$(READLINE)/include -L$(READLINE)/lib $(OBJS) $(LIBFT) -o $(NAME) -lreadline -lncurses

$(OBJS): | $(OBJ_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o: %.c
	gcc $(FLAGS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIRECTORY)

clean:
	$(MAKE) -C $(LIBFT_DIRECTORY) clean
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(LIBFT)
	rm -rf $(NAME)

re: fclean all
