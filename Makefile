# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acastilh <acastilh@student.42.rio>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/13 14:57:20 by acastilh          #+#    #+#              #
#    Updated: 2024/02/22 16:19:06 by acastilh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell
LOCLIBFT	= libft
LOCLHEADER	= header
SRCDIR		= src
OBJDIR		= obj
SRCS		= main.c \
			  builtins/ft_cd.c \
			  builtins/ft_cd_aux.c \
			  builtins/ft_echo.c \
			  builtins/ft_pwd.c \
			  builtins/ft_env.c \
			  builtins/ft_unset.c \
			  builtins/ft_export.c \
			  builtins/ft_exit.c \
			  signals/signals.c \
			  signals/signal_handlers.c \
			  execute/execute_command.c \
			  execute/execute_builtin.c \
			  execute/pipex.c \
			  execute/pipex_utils.c \
			  utils/utils.c \
			  utils/fd_utils.c \
			  utils/array_utils.c \
			  utils/string_utils.c \
			  utils/ft_split_except.c \
			  init_shell.c \
			  print_envp.c \
			  display_prompt.c \
			  free_memory.c \
			  print_error.c \
			  expand_variable/expand_variable.c \
			  expand_variable/variable_data_access.c \
			  parser/parse_input.c \
			  parser/parse_redirection.c \
			  parser/tokenizer.c \
			  parser/syntax_analyzer.c \

SRCS		:= $(addprefix $(SRCDIR)/,$(SRCS))
OBJS		:= $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
RM			= rm -f

all: $(NAME)

$(NAME): $(OBJS) $(LOCLIBFT)/libft.a
	gcc -o $(NAME) $(OBJS) -L$(LOCLIBFT) -lft -lreadline

$(LOCLIBFT)/libft.a:
	make -C $(LOCLIBFT)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	mkdir -p $(dir $@)
	gcc -Wall -Wextra -Werror -I$(LOCLHEADER) -c $< -o $@

clean:
	make clean -C $(LOCLIBFT)
	$(RM) -r $(OBJDIR)

fclean: clean
	make fclean -C $(LOCLIBFT)
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re





