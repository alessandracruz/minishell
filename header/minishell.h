/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastilh <acastilh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 14:27:31 by acastilh          #+#    #+#             */
/*   Updated: 2023/11/22 12:07:32 by acastilh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <errno.h>
# include <stdarg.h>
# include <signal.h>
# include <termios.h>

# define MAX_PATH_LENGHT 1024
# define TRUE 1
# define FALSE 0
# define MSGERROR "(Minishell): syntax error near unexpected token `newline'\n"

typedef struct s_envp
{
	char			*name;
	char			*value;
	char			*full;
	struct s_envp	*next;
}t_envp;

typedef struct cmd_node
{
    
}t_cmd_node;

typedef struct s_minishell
{
	t_envp	*l_envp;
}t_minishell;

// MAIN

void	print_envp(char **envp);
void	init_shell(t_minishell *shell, char **envp);
char	*display_prompt(void);
void	free_arguments(char **arguments);
void	free_env_list(t_envp *env_list);
void	print_error(const char *message);

// EXECUÇAÕ DE COMANDOS EXTERNOS: external_commands

void	execute_command(char *input, t_minishell *shell);
void	execute_external_command(char **arguments);
bool	execute_builtin(char **args, t_minishell *shell);

// BUILTINS

// FT_CD

void	change_directory(const char *path);
void	handle_home_directory(t_minishell *shell);
void	handle_oldpwd_directory(t_minishell *shell);
void	update_pwd_oldpwd(t_minishell *shell, char *old_dir);
void	ft_cd(char **args, t_minishell *shell);

// FT_ECHO

void	ft_echo(char **args, t_minishell *shell);

// UTILS

t_envp	*get_env_var(const char *name, t_envp *env_list);
void	update_env_var(const char *name, const char *value, t_envp **env_list);
void	print_env_list(t_envp *env_list);
void	add_env_var(t_envp **env_list, const char *name, const char *value);
char	*join_string_and_free(char *s1, char *s2);
char	*add_char_to_result(char *result, char c);

// EXPAND_VARIABLE

char	*expand_variable(char *var_name, t_minishell *shell);
char	*expand_variable_in_quotes(char *arg, t_minishell *shell, int *index);

// VARIABLE_DATA_ACCESS

char	*get_variable_name(const char *arg, int start);
char	*get_variable_value(const char *name, t_minishell *shell);

// HANDLE_QUOTES

char	*handle_quotes(char *arg, t_minishell *shell);

// QUOTE_PROCESSING

char	*process_single_quote(char *arg, int *index);
char	*process_double_quote_end(char *arg, char *result, int *index,
			int start);
char	*process_double_quotes(char *arg, t_minishell *shell, int *index);
char	*process_quotes(char *arg, t_minishell *shell);

#endif
