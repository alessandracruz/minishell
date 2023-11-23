/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analyzer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastilh <acastilh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 21:54:53 by acastilh          #+#    #+#             */
/*   Updated: 2023/11/23 00:30:08 by acastilh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_redirection(char *token)
{
	return (strcmp(token, ">") == 0 || strcmp(token, ">>") == 0
		|| strcmp(token, "<") == 0 || strcmp(token, "<<") == 0);
}

void	process_redirection(char **tokens, int *index, t_cmd_node *cmd)
{
	t_redirection	*redir;

	redir = parse_redirection(tokens, index);
	if (!redir)
		return ;
	if (strcmp(redir->type, ">") == 0 || strcmp(redir->type, ">>") == 0)
		cmd->output_redirection = redir;
	else if (strcmp(redir->type, "<") == 0 || strcmp(redir->type, "<<") == 0)
		cmd->input_redirection = redir;
}

bool is_quote(char c)
{
	return (c == '\'' || c == '\"');
}

void	add_argument_to_command(t_cmd_node *cmd, char *arg)
{
	if (cmd->arg_count >= MAX_ARGS)
	{
		print_error("Erro: maximum number of arguments exceeded.\n");
		return ;
	}
	cmd->args[cmd->arg_count] = ft_strdup(arg);
	if (cmd->args[cmd->arg_count] == NULL)
	{
		print_error("Erro: fails to allocate memory to the argument.\n");
		return ;
	}
	cmd->arg_count++;
}

void	process_quotes_syntax(char **tokens, int *index, t_cmd_node *cmd)
{
	char	*token;
	char	quote_type;
	char	*buffer;
	int		len;

	token = tokens[*index];
	quote_type = token[0];
	buffer = malloc(strlen(token) + 1);
	if (!buffer)
		return ;
	buffer[0] = '\0';
	while (tokens[*index])
	{
		token = tokens[*index];
		strcat(buffer, token);
		len = strlen(token);
		if (token[len - 1] == quote_type)
			break ;
		(*index)++;
	}
	add_argument_to_command(cmd, buffer);
	free(buffer);
	(*index)++;
}
