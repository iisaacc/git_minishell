/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carmarqu <carmarqu@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 16:02:59 by carmarqu          #+#    #+#             */
/*   Updated: 2024/02/06 13:31:23 by carmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_errors(char *str)
{
	if (str[0] == '=')
		return (0);
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
