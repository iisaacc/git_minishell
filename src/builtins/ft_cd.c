/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carmarqu <carmarqu@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 14:59:45 by carmarqu          #+#    #+#             */
/*   Updated: 2024/02/01 15:09:57 by carmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void ft_print_envp_list(t_envp *envp)//borrar despues
{
	t_envp	*tmp;

	tmp = envp;
	while (tmp != NULL)
	{
		printf("%s", tmp->id);
		printf("%s\n", tmp->value);
		tmp = tmp->next;
	}
}

void	change_env(t_envp **envp, char *find, char *new_value)
{
	t_envp *aux;

	aux = *envp;
	while (aux)
	{
		if(!ft_strncmp(aux->id, find, ft_strlen(find)))
		{
			free(aux->value);
			aux->value = ft_strdup(new_value);
			break ;
		}
		aux = aux->next;
	}
}

int	find_env(t_envp **envp, char *find)
{
	t_envp *aux;
		
	aux = *envp;
	while (aux)
	{
		if (!ft_strncmp(aux->id, find, ft_strlen(find)))
			return (1);
		aux = aux->next;
	}
	return (0);
}

void	ft_cd(t_mini *mini, t_envp **envp)//se llega hasta aqui full_cmd[1] sera el camino
{
	char *pwd;
	char *oldpwd;
	char buffer[1024];
	
	oldpwd = ft_strdup(getcwd(buffer, sizeof(buffer)));
	if (chdir(mini->full_cmd[1])) //devuleve 1 se falla
		return (free(oldpwd));
	pwd = ft_strdup(getcwd(buffer, sizeof(buffer)));
	change_env(envp, "PWD=", pwd);
	change_env(envp, "OLDPWD=", oldpwd);
	printf("PWD -> %s\n", pwd);
	printf("OLD -> %s\n", oldpwd);
	//ft_print_envp_list(envp);
	free(pwd);
	free(oldpwd);
}
