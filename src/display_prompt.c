/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_prompt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastilh <acastilh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 15:23:13 by acastilh          #+#    #+#             */
/*   Updated: 2023/11/16 12:49:36 by acastilh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*display_prompt(void)
{
	char	*input;
	char	cwd[MAX_PATH_LENGHT];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		input = readline(ft_strjoin("minishell:", ft_strjoin(cwd, "> ")));
	else
		input = readline("minishell> ");
	if (input && *input)
		add_history(input);
	return (input);
}
