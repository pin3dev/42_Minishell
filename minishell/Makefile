# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: clima-fr <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/18 17:28:35 by clima-fr          #+#    #+#              #
#    Updated: 2023/09/19 18:49:35 by ivbatist         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = builts/b_upd_array.c \
      builts/b_utils_1.c builts/b_utils_2.c \
      builts/b_utils_envp.c builts/b_utils_expo.c \
      builts/_cd.c builts/_echo.c builts/_env.c builts/_exit.c \
      builts/_export.c builts/_pwd.c builts/_unset.c \
      executor/e_cmd.c executor/e_heredoc.c executor/e_pipe.c \
      executor/e_redir.c executor/e_utils.c \
      expander/x_dollar.c expander/x_heredollar.c \
      expander/x_utils_dollar.c \
      lexer/lx_char_counter.c lexer/lx_cpy.c lexer/lx_heredoc_case.c \
      lexer/lx_heredoc_utils.c lexer/lx_tok_counter.c lexer/lx_type.c \
      lib/lb_lst_ast_1.c lib/lb_lst_ast_2.c lib/lb_lst_envp.c \
      lib/lb_lst_expo.c lib/libft_atoi.c lib/libft_char.c \
      lib/libft_cpy.c lib/libft_itoa.c lib/libft_mem.c lib/libft_split.c \
      lib/libft_str.c monitoring/m_checker.c monitoring/m_clean.c \
      monitoring/m_signal.c parser/p_lst_ast.c parser/p_tree_ast.c \
      parser/p_utils_lst_ast.c parser/p_utils_tree_ast.c \
      minishell.c \

OBJS = ${SRC:.c=.o}

CC = cc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror #-fsanitize=address
LFLAGS = -lreadline

.c.o:
	${CC} ${CFLAGS} ${INCLUDE} -c $< -o $@

$(NAME): ${OBJS}
	${CC} ${CFLAGS} ${INCLUDE} ${OBJS} ${LFLAGS} -o ${NAME}

all: ${NAME}

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re


