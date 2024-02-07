/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carmarqu <carmarqu@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 16:02:59 by carmarqu          #+#    #+#             */
/*   Updated: 2024/02/07 14:02:43 by carmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	export_error(char *str)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd("cd: ", 2);
	ft_putchar_fd('`', 2);
	ft_putstr_fd(str, 2);
	ft_putchar_fd('\'', 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd("not a valid identifier\n", 2);
	return (0);
}

int	check_errors(char *str)
{
	if (str[0] == '=')
		return (export_error(str));
	else if (!ft_strchr(str, '='))
		return (0);//escribir not a valid identifier
	return (1);
	
}

void	ft_export(t_envp **envp_list, char **new_var)
{
	char **splitted;
	char *id;
	char *value;
	int x;
	
	x = 0;
	while (new_var[x])
	{
		if (check_errors(new_var[x]) && new_var[x])//checkear si el formato es HOLA="hoal"
		{
			splitted = ft_split(new_var[x], '=');
			id = ft_strdup(splitted[0]);
			id = ft_strjoin(id, "=");
			if (splitted[1])
				value = ft_strdup(splitted[1]);
			if (!find_env(envp_list, id))
				add_new_envp(envp_list, envp_new(new_var[x]));
			else
				change_env(envp_list, id, value);
			free(id);
			if (splitted[1])
				free(value);
			ft_free_2d(splitted);
		}
		x++;
	}
}
