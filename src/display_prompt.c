/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_prompt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matlopes <matlopes@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 15:23:13 by acastilh          #+#    #+#             */
/*   Updated: 2024/03/06 08:33:24 by matlopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*display_prompt(void)
{
	char	*input;
	char	cwd[MAX_PATH_LENGHT];
	char	*temp;
	char	*prompt;

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		temp = ft_strjoin(cwd, "> ");
		prompt = ft_strjoin("minishell:", temp);
		free(temp);
		input = readline(prompt);
		free(prompt);
	}
	else
		input = readline("minishell> ");
	if (input && *input)
		add_history(input);
	return (input);
}
