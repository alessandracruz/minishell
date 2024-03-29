# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: matlopes <matlopes@student.42.rio>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/13 14:57:20 by acastilh          #+#    #+#              #
#    Updated: 2024/03/10 16:22:12 by matlopes         ###   ########.fr        #
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
			  builtins/ft_export_aux.c \
			  builtins/ft_exit.c \
			  signals/signals.c \
			  signals/signals_utils.c \
			  redirects/heredoc.c \
			  redirects/redirects.c \
			  execute/get_cmds.c \
			  execute/execute_command.c \
			  execute/execute_builtin.c \
			  execute/pipex.c \
			  execute/pipex_utils.c \
			  utils/utils.c \
			  utils/quotes_utils.c \
			  utils/fd_utils.c \
			  utils/array_utils.c \
			  utils/string_utils.c \
			  utils/free_utils.c \
			  utils/ft_split_except.c \
			  utils/ft_split_trim.c \
			  utils/ft_split_quotes.c \
			  init_shell.c \
			  print_envp.c \
			  display_prompt.c \
			  free_memory.c \
			  print_error.c \
			  expand_variable/expand_variable.c \
			  expand_variable/variable_data_access.c \

SRCS		:= $(addprefix $(SRCDIR)/,$(SRCS))
OBJS		:= $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
RM			= rm -f

all: $(NAME)

$(NAME): $(OBJS) $(LOCLIBFT)/libft.a
	gcc -g -o $(NAME) $(OBJS) -L$(LOCLIBFT) -lft -lreadline

$(LOCLIBFT)/libft.a:
	make -C $(LOCLIBFT)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	mkdir -p $(dir $@)
	gcc -g -Wall -Wextra -Werror -I$(LOCLHEADER) -c $< -o $@

clean:
	make clean -C $(LOCLIBFT)
	$(RM) -r $(OBJDIR)

fclean: clean
	make fclean -C $(LOCLIBFT)
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
