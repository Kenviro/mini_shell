NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRCDIR = src/
OBJDIR = obj/
LIBFT_DIR = ./Libft

SRC =	$(SRCDIR)minishell.c \
		$(SRCDIR)holy_split.c	\
		$(SRCDIR)splitonsteroids.c \
		$(SRCDIR)error.c

OBJ = $(patsubst $(SRCDIR)%, $(OBJDIR)%, $(SRC:.c=.o))

HEADER = includes/minishell.h
LIBFT = $(LIBFT_DIR)/libft.a
INCLUDES = -I includes -I $(LIBFT_DIR) -I /usr/include/readline

READLINE_LIBS = -L/usr/lib -lreadline -lncurses

all: $(OBJDIR) $(LIBFT) $(NAME)

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -L$(LIBFT_DIR) -lft $(READLINE_LIBS) -o $(NAME)

$(OBJDIR)%.o: $(SRCDIR)%.c $(HEADER)
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

.PHONY: all clean fclean re
