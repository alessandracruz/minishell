/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastilh <acastilh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 15:41:40 by acastilh          #+#    #+#             */
/*   Updated: 2023/11/15 22:28:41 by acastilh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_env_from_entry(char *entry, t_envp **env_list)
{
	char	*equal_sign;
	int		name_length;
	char	*name;
	char	*value;

    equal_sign = strchr(entry, '=');
    if (equal_sign != NULL)
    {
        name_length = equal_sign - entry;
        name = malloc(name_length + 1);
        if (name == NULL)
        {
            return	;
        }
        strncpy(name, entry, name_length);
        name[name_length] = '\0';

        value = strdup(equal_sign + 1);
        if (value == NULL)
        {
			free(name);
            return ;
        }
        add_env_var(env_list, name, value);
        free(name);
    }
}

void	init_shell(t_minishell *shell, char **envp)
{
	int i = 0;
    char *entry;
    char *equal_sign;
    shell->l_envp = NULL;

    while (envp[i] != NULL) {
        entry = envp[i];
        equal_sign = strchr(entry, '=');

        if (equal_sign != NULL) {
            int name_length = equal_sign - entry;
            char *name = malloc(name_length + 1);
            strncpy(name, entry, name_length);
            name[name_length] = '\0';

            char *value = strdup(equal_sign + 1);

            add_env_var(&shell->l_envp, name, value);

            free(name);
            // Não precisa liberar 'value' aqui, pois é gerenciado pela lista env
        }
        i++;
    }
}

