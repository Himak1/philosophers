
NAME = philo

VPATH = src:src/input

SRC_FILES = main.c\
			philo_loop.c\
			p_eat.c\
			pthread_functions.c\
			time_functions.c\
			print_messages.c\
			mutex_gates.c\
			mutex_functions.c\
			monitor_philos.c\
			$(INPUT_FILES)

INPUT_FILES = get_parameters.c\
				ft_sfatoi.c\
				isnum_str.c\

OBJ = $(addprefix obj/, $(SRC_FILES:.c=.o))

INC = -Iinclude

CFLAGS = -Wextra -Wall -Werror $(INC) -pthread -o3
all: $(NAME)

$(NAME): $(OBJ)
		$(CC) $(CFLAGS) -o $@ $^

obj/%.o: %.c
		@mkdir -p obj
		$(CC) -c $(CFLAGS) -o $@ $^

clean:
	rm -rf obj

fclean: clean
		rm -rf philo

re: fclean all

.PHONY: all clean fclean re
