/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastilh <acastilh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 16:10:12 by acastilh          #+#    #+#             */
/*   Updated: 2024/02/03 20:53:43 by acastilh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_pwd(t_minishell *shell)
{
	(void)shell;
	char	cwd[MAX_PATH_LENGHT];

	(void)shell;
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		ft_putstr_fd(cwd, STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
	}
	else
	{
		ft_putstr_fd("pwd: error retrieving current ", STDERR_FILENO);
		ft_putstr_fd("directory\n", STDERR_FILENO);
		return (false);
	}
	return (true);
}
