/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carmarqu <carmarqu@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 16:02:59 by carmarqu          #+#    #+#             */
/*   Updated: 2024/01/31 16:08:16 by carmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* int	find_equal(char *str)
{
	int x;

	x = 0;
	while (str[x])
	{
		if (str[x] == '=')
			return (++x); //pos de =
		x++;
	}
	return (0);//si no encuentra
} */

char	*out_quotes(char *str)//Aún no quita las comillas si están en medio del comando
{
	int x;

	x = 1;
	if(str[0] == '\'' || str[0] == '"')
		str = ft_substr(str, 1, ft_strlen(str) - 2);
	return (str);
}

void	ft_export(t_envp **envp_list, char **new_var, t_mini *mini)
{
	char **splitted;
	char *id;
	char *value;

	int x;
	
	x = 0;
	//ft_print_split(new_var);	//eso es un problema, no estan separado por comillas
	splitted = ft_split(new_var[x], '=');
	id = ft_strdup(splitted[0]);
	id = ft_strjoin(id, "=");
	value = ft_strdup(splitted[1]);
	mini->id = 1;
	value = out_quotes(value);
	if (!find_env(envp_list, id))
		add_new_envp(envp_list, envp_new(new_var[x]));
	else
		change_env(envp_list, id, value);
	ft_print_envp_list(envp_list);//sigue el problema de las listas solo cambiarem al momento
	printf("fin\n");
}
