/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matlopes <matlopes@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 14:27:31 by acastilh          #+#    #+#             */
/*   Updated: 2024/03/04 15:28:01 by matlopes         ###   ########.fr       */
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

# define EXIT_DENIED 126
# define EXIT_NOTFOUND 127
# define EXIT_FORK 130
# define EXIT_QUITFORK 131

extern int	g_signal_exit;

typedef struct s_envp
{
	char			*name;
	char			*value;
	char			*full;
	struct s_envp	*next;
}	t_envp;

typedef struct s_redirection
{
	char	*type;
	char	*filename;
}	t_redirection;

typedef struct s_get_file
{
	int		fd;
	int		index;
	int		check;
	char	*temp;
	int		counter;
}	t_get_file;

typedef struct s_execute
{
	char	**cmds;
	pid_t	*pids;
	int		start;
	int		current;
	int		amount;
	int		fd_files[2];
	int		fds[2];
}	t_execute;

typedef struct s_minishell
{
	t_envp		*l_envp;
	int			exit;
	int			heredoc_exit;
}	t_minishell;

// SRC

void			free_redirection(t_redirection *redir);
void			free_env_list(t_envp *env_list);
void			free_memory(t_minishell *shell);
void			print_envp(char **envp);
void			init_shell(t_minishell *shell, char **envp);
void			add_env_from_entry(char *entry, t_envp **env_list);
char			*display_prompt(void);
void			cmd_print_error(const char *message, const char *error);
int				print_error(const char *message, const char *error);

// MAIN

int				main(int argc, char **argv, char **envp);

// REDIRECTS

char			*heredoc(char *input, int index, t_execute *execute,
					t_minishell *shell);
int				get_redirect_amount(char redirect, char *input);
int				get_filein(char *input, t_execute *execute, t_minishell *shell);
int				get_fileout(char *input, t_execute *execute,
					t_minishell *shell);

// EXECUTE

void			execute_command(char **input, t_minishell *shell);
void			ft_pipex(t_execute *execute, t_minishell *shell);
void			ft_execute_cmd(char *argv, t_minishell *shell);

// BUILTINS

bool			is_builtin(char *cmd);
bool			execute_builtin(char **args, t_minishell *shell);

// FT_CD

void			change_directory(const char *path);
void			update_pwd_oldpwd(t_minishell *shell, char *old_dir);
bool			ft_cd(char **args, t_minishell *shell);

// FT_CD_AUX

void			handle_home_directory(t_minishell *shell);
void			handle_oldpwd_directory(t_minishell *shell);
char			*expand_tilde(char *path, t_minishell *shell);

// FT_ECHO

int				ft_printnv(char *str, t_minishell *shell, int size,
					bool check_env);
bool			ft_echo(char **args, t_minishell *shell);

// FT_PWD

bool			ft_pwd(t_minishell *shell);

// FT_ENV

bool			ft_env(t_minishell *shell);

// FT_UNSET

void			remove_env_var(t_envp **l_envp, char *var_name);
bool			ft_unset(char **args, t_minishell *shell);

// FT_EXPORT

bool			is_valid_var_name(char *name);
char			*handle_export_quotes(char **arg, char **name, char **value);
int				add_or_update_env_var(t_minishell *shell, char *name,
					char *value);
void			handle_export_argument(t_minishell *shell, char **arg);
void			list_environment_variables(t_minishell *shell);
bool			ft_export(char **args, t_minishell *shell);

// FT_EXIT

bool			is_valid_exit_argument(char *arg);
void			print_exit_error(char **args, int *exit_status);
bool			ft_exit(char **args, t_minishell *shell);

// SIGNALS

void			handle_sigint(int sig);
void			handle_sigquit(int sig);
void			sig_new_line(int sig);
void			sig_heredoc_break(int sig);
void			sig_empty(int sig);
void			run_signals(void);

// UTILS

void			fd_dup_close(int fd, int change);
void			free_arguments(char **arguments);
int				arguments_counter(char **argv);
t_envp			*get_env_var(const char *name, t_envp *env_list);
void			update_env_var(const char *name, const char *value,
					t_envp **env_list);
void			print_env_list(t_envp *env_list);
char			**get_envp(t_envp *envp);
bool			add_env_var(t_envp **env_list, const char *name,
					const char *value);
int				ft_is_quote(char c);
int				ft_check_quote(char const *s);
int				ft_check_inside_quotes(char const *s, int index);
char			*ft_cutstr(char *str, int start, int len);
char			*join_string_and_free(char *s1, char *s2);
char			*add_char_to_result(char *result, char c);
char			**ft_split_except(char const *s, char c);
char			**ft_split_trim(char const *s, char *c, char *set);
char			**ft_split_quotes(char const *s);
void			double_free(char *s1, char *s2);

// EXPAND_VARIABLE

char			*expand_variable(char *var_name, t_minishell *shell);
char			*expand_variable_in_quotes(char *arg, t_minishell *shell,
					int *index);

// VARIABLE_DATA_ACCESS

char			*get_variable_name(const char *arg, int start);
char			*get_variable_value(const char *name, t_minishell *shell);

#endif
