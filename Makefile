# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: egiraldi <egiraldi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/27 09:07:49 by egiraldi          #+#    #+#              #
#    Updated: 2023/02/27 13:03:34 by egiraldi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:=	minishell

CC			:=	gcc
CFLAGS		:=	-Wall -Wextra -Werror -g

OBJ_FOLDER	:=	objs
SRC_FOLDER	:=	srcs

HEADERFILE	:=	minishell.h
SRCS		:=	ft_minishell.c 				\
				builtins/ft_cd.c 			\
				builtins/ft_echo.c 			\
				builtins/ft_exit.c 			\
				builtins/ft_env0.c 			\
				builtins/ft_env1.c 			\
				builtins/ft_env2.c 			\
				builtins/ft_export0.c 		\
				builtins/ft_export1.c 		\
				builtins/ft_pwd.c 			\
				builtins/ft_unset.c 		\
				bonus/ft_wildcard0.c 		\
				bonus/ft_wildcard1.c 		\
				errors/ft_error0.c 			\
				errors/ft_error1.c 			\
				errors/ft_error2.c 			\
				executor/ft_read_loop.c 	\
				executor/ft_commands0.c 	\
				executor/ft_commands1.c 	\
				executor/ft_executable.c 	\
				executor/ft_pipe.c			\
				executor/ft_redirect0.c 	\
				executor/ft_redirect1.c 	\
				executor/ft_redirect2.c 	\
				utils/ft_get_next_line.c 	\
				utils/ft_utils0.c 			\
				utils/ft_utils1.c 			\
				utils/ft_utils2.c 			\
				utils/ft_utils3.c 			\
				utils/ft_utils4.c 			\
				utils/ft_utils5.c 			\
				utils/ft_utils6.c 			\
				utils/ft_split.c 			\
				parser/ft_parser0.c 		\
				parser/ft_parser1.c 		\
				parser/ft_parser2.c 		\
				parser/ft_parser3.c 		\
				parser/ft_parser4.c 		\
				parser/ft_parser5.c 		\
				signals/ft_signals.c 		\
				signals/ft_signal_handler.c \
				gc/ft_gc.c 					\
				gc/ft_plst.c 				\
				gc/ft_plst1.c
OBJS		:= $(SRCS:%.c=$(OBJ_FOLDER)/%.o)

.SUFIXES:

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -L/usr/local/opt/readline/lib -lreadline -o $(NAME)

$(OBJS): $(OBJ_FOLDER)/%.o: $(SRC_FOLDER)/%.c $(HEADERFILE) Makefile
	@mkdir -p $(@D)
	$(CC) -c $(CFLAGS) -I/usr/local/opt/readline/include/ -o $@ $<

clean:
	rm -fr $(OBJ_FOLDER)

fclean: clean
	rm -fr $(NAME)

re: fclean all

.PHONY: all clean fclean re