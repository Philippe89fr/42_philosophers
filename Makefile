NAME        = philo

SRCS        = srcs/main.c \
				srcs/liberator_god.c \
				srcs/lst_maker.c \
				srcs/lst_maker2.c \
				srcs/init_struct.c \
				srcs/error_management.c \
				srcs/time_management.c \
				srcs/routine_management.c \
				srcs/routine_management_utils.c \
				srcs/routine_management_100.c \
				srcs/parsing.c \
				srcs/routine_management_utils2.c

OBJS        = $(SRCS:%.c=%.o)

CC          = cc
CFLAGS      = -g3 -pthread -Isrcs

# Run 'make re MODE=pretty' for color formatting.
# Run 'make re MODE=debug' for debug formatting.
MODE    = none
ifeq ($(MODE), pretty)
    CFLAGS    += -D DEBUG_FORMATTING=1
endif
ifeq ($(MODE), debug)
    CFLAGS    += -D DEBUG_FORMATTING=1 -fsanitize=thread -g
endif

RM          = rm -rf

# Construction de l'exécutable standard
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

# Transformation des .c en .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Règles principales
all: $(NAME)

clean:
	$(RM) $(OBJS) 

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
