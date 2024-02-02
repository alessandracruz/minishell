/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matlopes <matlopes@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 14:27:31 by acastilh          #+#    #+#             */
/*   Updated: 2024/02/02 12:51:31 by matlopes         ###   ########.fr       */
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
# define MAX_ARGS 256
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

typedef struct s_redirection
{
	char	*type;
	char	*filename;
}t_redirection;

typedef struct cmd_node
{
	char			*command;
	char			*args[MAX_ARGS];
	int				arg_count;
	t_redirection	*input_redirection;
	t_redirection	*output_redirection;
}t_cmd_node;

typedef struct execute
{
	char	**cmds;
	int		cmds_size;
	int		hasFiles[2];
	int		fd_files[2];
}t_execute;

typedef struct s_minishell
{
	t_envp		*l_envp;
	t_cmd_node	*current_cmd;
}t_minishell;

// SRC

void			free_redirection(t_redirection *redir);
void			free_cmd_node(t_cmd_node *cmd);
void			free_env_list(t_envp *env_list);
void			free_memory(t_minishell *shell);
void			print_envp(char **envp);
void			init_shell(t_minishell *shell, char **envp);
void			add_env_from_entry(char *entry, t_envp **env_list);
char			*display_prompt(void);
void			print_error(const char *message, const char *error);

// MAIN

int				main(int /* argc */, char ** /* argv */, char **envp);

// EXECUÇAÕ DE COMANDOS EXTERNOS: external_commands

bool			is_builtin(char *cmd);
bool			execute_builtin(char **args, t_minishell *shell);
void			execute_command(char *input, t_minishell *shell, char **envp);
void			ft_pipex(t_execute *execute, t_minishell *shell, char *envp[]);
void			ft_execute_cmd(char *argv, t_minishell *shell, char *envp[]);

// BUILTINS

// FT_CD

void			change_directory(const char *path);
void			handle_home_directory(t_minishell *shell);
void			handle_oldpwd_directory(t_minishell *shell);
void			update_pwd_oldpwd(t_minishell *shell, char *old_dir);
bool			ft_cd(char **args, t_minishell *shell);

// FT_ECHO

bool			ft_echo(char **args, t_minishell *shell);

// UTILS

void			free_arguments(char **arguments);
int				arguments_counter(char **argv);
t_envp			*get_env_var(const char *name, t_envp *env_list);
void			update_env_var(const char *name, const char *value,
					t_envp **env_list);
void			print_env_list(t_envp *env_list);
bool			add_env_var(t_envp **env_list, const char *name,
					const char *value);
char			*join_string_and_free(char *s1, char *s2);
char			*add_char_to_result(char *result, char c);
char			**ft_split_except(char const *s, char c);

// EXPAND_VARIABLE

char			*expand_variable(char *var_name, t_minishell *shell);
char			*expand_variable_in_quotes(char *arg, t_minishell *shell,
					int *index);

// VARIABLE_DATA_ACCESS

char			*get_variable_name(const char *arg, int start);
char			*get_variable_value(const char *name, t_minishell *shell);

// HANDLE_QUOTES

char			*handle_quotes(char *arg, t_minishell *shell);

// QUOTE_PROCESSING

char			*process_single_quote(char *arg, int *index);
char			*process_double_quote_end(char *arg, char *result, int *index,
					int start);
char			*process_double_quotes(char *arg, t_minishell *shell,
					int *index);
char			*process_quotes(char *arg, t_minishell *shell);

// PARSE

// PARSE_INPUT

t_cmd_node		*parse_input(char *input);

// PARSE_REDIRECTION

t_redirection	*parse_redirection(char **tokens, int *index);
void			apply_output_redirections(t_cmd_node *cmd);
void			apply_simple_input_redirection(t_cmd_node *cmd);
void			apply_here_document(t_cmd_node *cmd);
void			apply_input_redirections(t_cmd_node *cmd);

// TOKENIZER

int				is_delimiter(char c, char delimiter);
int				count_tokens(char *input, char delimiter);
char			**tokenize_input(char *input, char delimiter);
void			parse_token(char **tokens, int *index, t_cmd_node *cmd);

// SYNTAX_ANALYZER

bool			is_redirection(char *token);
void			process_redirection(char **tokens, int *index, t_cmd_node *cmd);
bool			is_quote(char c);
void			add_argument_to_command(t_cmd_node *cmd, char *arg);
void			process_quotes_syntax(char **tokens, int *index,
					t_cmd_node *cmd);

#endif
