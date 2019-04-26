NAME		:= lem-in
CC			:=	gcc
CFLAGS		:=	-Wall -Wextra -Werror

SOURCES_DIR	:= ./src/
OBJECTS_DIR	:= ./obj/
INCLUDE_DIR	:= ./inc/
LIB_DIR		:= ./lib/
SOURCES		:=	main.c \
				save_input.c

OBJECTS		:= $(addprefix $(OBJECTS_DIR), $(SOURCES:.c=.o))

LIBFT		= $(LIBFT_DIR)libft.a
LIBFT_DIR	:= $(LIB_DIR)libft
LIBFT_INC	:= $(LIBFT_DIR)
LIBFT_FL	:= -lft -L $(LIBFT_DIR)
PRINTF_FL	:= $(LIB_DIR)ft_printf/libftprintf.a
PRINTF_INC	:= $(LIB_DIR)ft_printf

LIB_FLAGS	:= $(LIBFT_FL) $(PRINTF_FL)

HEADER_FLAGS	:= -I $(INCLUDE_DIR) -I $(LIBFT_INC) -I $(PRINTF_INC)

all:	$(NAME)

$(NAME): $(LIBFT) $(OBJECTS)
		$(CC) $(CFLAGS) $(OBJECTS) $(LIB_FLAGS) -o $(NAME)

$(OBJECTS): | $(OBJECTS_DIR)

$(OBJECTS_DIR):
		mkdir $(OBJECTS_DIR)

$(OBJECTS_DIR)%.o: %.c
		$(CC)  $(CFLAGS) -c $< -o $@ $(HEADER_FLAGS)

$(LIBFT):
		make -C $(LIBFT_DIR)

clean:
	rm -rf $(OBJECTS)
	make clean -C $(LIBFT_DIR)

fclean: clean
	rm -rf $(NAME)
	rm -rf $(OBJECTS_DIR)
	make fclean -C $(LIBFT_DIR)

re: fclean all

vpath %.c $(SOURCES_DIR)
