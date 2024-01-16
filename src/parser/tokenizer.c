/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matlopes <matlopes@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 21:41:59 by acastilh          #+#    #+#             */
/*   Updated: 2024/01/16 16:44:31 by matlopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_delimiter(char c, char delimiter)
{
	return (c == delimiter || c == '\0');
}

int	count_tokens(char *input, char delimiter)
{
	int	count;
	int	in_token;

	count = 0;
	in_token = 0;
	while (*input)
	{
		if (is_delimiter(*input, delimiter) && in_token)
		{
			in_token = 0;
			count++;
		}
		else if (!is_delimiter(*input, delimiter))
			in_token = 1;
		input++;
	}
	if (in_token)
		return (count + 1);
	else
		return (count);
}

char	**tokenize_input(char *input, char delimiter)
{
	char	**tokens;

	tokens = ft_split(input, delimiter);
	if (!tokens)
		return (NULL);
	return (tokens);
}

void	parse_token(char **tokens, int *index, t_cmd_node *cmd)
{
	char	*token;

	token = tokens[*index];
	if (*index == 0)
	{
		cmd->command = ft_strdup(token);
	}
	else if (is_redirection(token))
	{
		process_redirection(tokens, index, cmd);
	}
	else
	{
		add_argument_to_command(cmd, token);
	}
	(*index)++;
}
