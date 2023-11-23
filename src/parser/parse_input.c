/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastilh <acastilh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 18:21:39 by acastilh          #+#    #+#             */
/*   Updated: 2023/11/22 23:54:00 by acastilh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd_node	*parse_input(char *input)
{
	char		**tokens;
	char		delimiter;
	t_cmd_node	*cmd;
	int			index;

	delimiter = ' ';
	tokens = tokenize_input(input, delimiter);
	if (!tokens)
		return (NULL);
	cmd = malloc(sizeof(t_cmd_node));
	if (!cmd)
	{
		free(tokens);
		return (NULL);
	}
	index = 0;
	while (tokens[index])
	{
		parse_token(tokens, &index, cmd);
		index++;
	}
	free(tokens);
	return (cmd);
}
