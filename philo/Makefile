NAME	=	philo

CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror
RM		=	rm -f

FILES	=	philo.c \
			utils.c	\
			print.c \
			init_data.c \
			monitoring.c \
			dinner.c \
			routines.c \

FtoO	=	$(FILES:.c=.o)

all : $(NAME)

$(NAME):	$(FtoO)
	$(CC) $(CFLAGS) $(FtoO) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(FtoO)

fclean: clean
	$(RM) $(NAME) $(FtoO)

re: fclean $(NAME)

.PHONY: all clean fclean re
