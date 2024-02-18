/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastilh <acastilh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 19:45:06 by acastilh          #+#    #+#             */
/*   Updated: 2024/02/16 20:45:55 by acastilh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool    is_valid_var_name(char *name)
{
    if (!ft_isalpha(*name) && *name != '_')
        return (false);
    name++;
    while (*name)
    {
        if (!ft_isalnum(*name) && *name != '_')
            return (false);
        name++;
    }
    return (true);
}

void    add_or_update_env_var(t_minishell *shell, char *name, char *value)
{
    t_envp *env_var = shell->l_envp;
    while (env_var)
    {
        if (ft_strcmp(env_var->name, name) == 0)
        {
            free(env_var->value);
            env_var->value = ft_strdup(value);
            return ;
        }
        env_var = env_var->next;
    }
    t_envp *new_var = (t_envp *)malloc(sizeof(t_envp));
    if (new_var == NULL)
        return ;
    new_var->name = ft_strdup(name);
    new_var->value = ft_strdup(value);
    new_var->next = shell->l_envp;
    shell->l_envp = new_var;
}

void handle_export_argument(t_minishell *shell, char *arg)
{
    char *equal_sign = ft_strchr(arg, '=');
    if (equal_sign != NULL)
    {
        *equal_sign = '\0';
        if (is_valid_var_name(arg))
        {
            add_or_update_env_var(shell, arg, equal_sign + 1);
        }
        else
        {
            ft_printf("export: `%s': not a valid identifier\n", arg);
        }
        *equal_sign = '=';
    }
    else
    {
        if (is_valid_var_name(arg))
        {
            if (!get_env_var(arg, shell->l_envp))
            {
                add_or_update_env_var(shell, arg, "");
            }
        }
        else
        {
            ft_printf("export: `%s': not a valid identifier\n", arg);
        }
    }
}

void list_environment_variables(t_minishell *shell)
{
    t_envp *current = shell->l_envp;
    while (current != NULL)
    {
        if (current->value != NULL)
        {
            printf("declare -x %s=\"%s\"\n", current->name, current->value);
        }
        else
        {
            printf("declare -x %s\n", current->name);
        }
        current = current->next;
    }
}

bool ft_export(char **args, t_minishell *shell)
{
    if (args[1] == NULL)
    {
        list_environment_variables(shell);
        return (true);
    }
    int i = 1;
    while (args[i] != NULL)
    {
        handle_export_argument(shell, args[i]);
        i++;
    }
    return (true);
}
