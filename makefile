NAME= philo
SRC= philosopher.c utils1.c state.c printers.c
SRCPATH= ./cfiles/
OBJ= $(SRC:.c=.o)
OBJS= $(addprefix $(OBJPATH), $(OBJ))
SRCS= $(addprefix $(SRCPATH), $(SRC))
OBJPATH= ./ofiles/

CC= gcc -Wall -Wextra -Werror -pthread -g
all: $(NAME)

$(OBJPATH)%.o: $(SRCPATH)%.c
	mkdir -p ofiles
	$(CC) -I./hfiles -o $@ -c $<

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME) -I./hfiles

clean:
	rm -f $(OBJS)
	rm -rf ofiles

fclean: clean
	rm -f $(NAME)

re: fclean all
