NAME = minitalk
CC = cc
RM = rm -rf
FLAGS = -Wall -Wextra -Werror

NAME_SERVER = server
NAME_CLIENT = client

SRCS_SERVER = server.c
SRCS_CLIENT = client.c

OBJS_SERVER = $(SRCS_SERVER:.c=.o)
OBJS_CLIENT = $(SRCS_CLIENT:.c=.o)

all: $(NAME)

$(NAME): $(NAME_SERVER) $(NAME_CLIENT)

$(NAME_SERVER): $(OBJS_SERVER)
	$(CC) $(FLAGS) $(OBJS_SERVER) -o $(NAME_SERVER)

$(NAME_CLIENT): $(OBJS_CLIENT)
	$(CC) $(FLAGS) $(OBJS_CLIENT) -o $(NAME_CLIENT)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

bonus: server_bonus client_bonus

server_bonus: server_bonus.c
	$(CC) $(FLAGS) server_bonus.c -o server_bonus

client_bonus: client_bonus.c
	$(CC) $(FLAGS) client_bonus.c -o client_bonus

clean:
	$(RM) $(OBJS_SERVER) $(OBJS_CLIENT)

fclean: clean
	$(RM) $(NAME_SERVER) $(NAME_CLIENT) server_bonus client_bonus

re: fclean all

.PHONY: all clean fclean re bonus