/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matlopes <matlopes@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 15:03:30 by matlopes          #+#    #+#             */
/*   Updated: 2024/03/10 17:55:15 by matlopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_cmd_quotes(char *cmd)
{
	int		save;
	int		index;
	char	*tmp1;
	char	*tmp2;
	char	*tmp3;

	index = -1;
	while (cmd[++index])
	{
		if (ft_is_quote(cmd[index]) && ft_check_quote(cmd + index))
		{
			save = index + ft_check_quote(cmd);
			tmp1 = ft_substr(cmd, index + 1, ft_check_quote(cmd + index) - 1);
			tmp2 = join_string_and_free(ft_substr(cmd, 0, index), tmp1);
			free(tmp1);
			tmp1 = ft_substr(cmd, index + ft_check_quote(cmd + index) + 1,
					ft_strlen(cmd));
			tmp3 = join_string_and_free(tmp2, tmp1);
			free(tmp1);
			free(cmd);
			cmd = tmp3;
			index = save - 2;
		}
	}
	return (cmd);
}

char	*get_cmd_env(char *cmd, int *index, t_minishell *shell)
{
	char	*tmp1;
	char	*tmp2;
	char	*tmp3;
	char	*var_value;
	int		counter;

	counter = *index;
	if (cmd[*index + 1] == '?')
	{
		var_value = ft_itoa(shell->exit);
		*index += 2;
	}
	else
		var_value = expand_variable_in_quotes(cmd, shell, index);
	tmp1 = ft_substr(cmd, 0, counter);
	tmp2 = ft_substr(cmd, *index, ft_strlen(cmd) - *index);
	tmp3 = ft_strjoin(tmp1, var_value);
	double_free(tmp1, var_value);
	cmd = ft_strjoin(tmp3, tmp2);
	double_free(tmp3, tmp2);
	return (cmd);
}

char	*get_cmd_value(char *cmd, t_minishell *shell)
{
	char	*str;
	char	*pointer;
	int		counter;

	str = ft_strdup(cmd);
	counter = 0;
	while (str[counter])
	{
		if (str[counter] == '$' && str[counter + 1] && str[counter + 1] != ' ')
		{
			if (ft_check_inside_squotes(str, counter) != -1)
				counter += ft_check_inside_squotes(str, counter);
			else
			{
				pointer = str;
				str = get_cmd_env(str, &counter, shell);
				free(pointer);
			}
		}
		if (str[counter])
			counter++;
	}
	return (str);
}

t_cmd	*get_cmd(char *cmd, t_minishell *shell)
{
	char	*temp;
	t_cmd	*new_cmd;

	new_cmd = malloc(sizeof(t_cmd));
	if (!new_cmd)
		return (NULL);
	new_cmd->fd[0] = 0;
	new_cmd->fd[1] = 1;
	temp = get_cmd_value(cmd, shell);
	new_cmd->cmd = get_cmd_quotes(temp);
	new_cmd->next = NULL;
	if (!get_redirect("<<", heredoc, new_cmd, shell)
		|| !get_redirect("<", filein, new_cmd, shell)
		|| !get_redirect(">", fileout, new_cmd, shell))
		return (NULL);
	return (new_cmd);
}

int	get_cmds(char **input, t_execute *execute, t_minishell *shell)
{
	t_get_cmds	get;
	t_cmd		*pointer;

	get.i = -1;
	get.start = NULL;
	get.cmds = ft_split_trim(*input, "|", " ");
	while (get.cmds[++get.i])
	{
		pointer = get_cmd(get.cmds[get.i], shell);
		if (!pointer)
			return (free_arguments(get.cmds), free_cmds(&get.start));
		pointer->index = get.i;
		if (!get.i)
		{
			get.start = pointer;
			get.move = pointer;
		}
		else
		{
			get.move->next = pointer;
			get.move = get.move->next;
		}
	}
	return (execute->cmds = get.start, execute->amount = get.i,
		free_arguments(get.cmds), 0);
}
