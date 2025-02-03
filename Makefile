NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRCDIR = src/
OBJDIR = obj/
LIBFT_DIR = ./Libft

SRC = $(SRCDIR)minishell.c
OBJ = $(patsubst $(SRCDIR)%.c, $(OBJDIR)%.o, $(SRC))

HEADER = includes/minishell.h
LIBFT = $(LIBFT_DIR)/libft.a
INCLUDES = -I includes -I $(LIBFT_DIR) -I /usr/include/readline

READLINE_LIBS = -lreadline -lhistory -L/usr/lib

all: $(LIBFT) $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -L$(LIBFT_DIR) -lft $(READLINE_LIBS) -o $(NAME)

$(OBJDIR)%.o: $(SRCDIR)%.c $(HEADER)
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	rm -rf $(OBJDIR)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all bonus clean fclean re header