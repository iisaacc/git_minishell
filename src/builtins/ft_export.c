/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isporras <isporras@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 16:02:59 by carmarqu          #+#    #+#             */
/*   Updated: 2024/01/31 12:03:30 by isporras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	find_equal(char *str)
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
}

char	*join_all(char **cmds)
{
	char *final;

	int x;
	x = 2;
	final = ft_strdup(cmds[1]);
	while (cmds[x])
	{
		final = ft_strjoin(final, cmds[x]);
		x++;
	}
	return (final);
}

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
	char *final;

	ft_print_split(mini->full_cmd);	//eso es un problema, no estan separado por comillas
	final = ft_strdup(join_all(new_var));
	printf("%s\n", final);
	splitted = ft_split(final, '=');
	id = ft_strdup(splitted[0]);
	id = ft_strjoin(id, "=");
	value = ft_strdup(splitted[1]);
	printf("%s\n", id);
	printf("%s\n", value);
	printf("%s\n", (*envp_list)->id);
	mini->id = 0;
	/* find_env(envp_list, "hola");
	mini->id = 1;
	printf("%s\n", id);
	value = out_quotes(value);
	if (!find_env(envp_list, id))
		add_new_envp(envp_list, envp_new(new_var));
	printf("%s\n", value);  */
}
