/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carmarqu <carmarqu@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 14:59:45 by carmarqu          #+#    #+#             */
/*   Updated: 2024/01/30 15:00:40 by carmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* void ft_print_envp_list(t_envp **envp)
{
	t_envp	*tmp;

	tmp = *envp;
	while (tmp != NULL)
	{
		printf("%s\n", tmp->id);
		printf("value: %s\n", tmp->value);
		tmp = tmp->next;
	}
} */

void	change_env(t_envp **envp, char *find, char *new_value)
{
	t_envp *aux;

	aux = *envp;
	while (aux->next)
	{
		if(!ft_strncmp(aux->id, find, ft_strlen(find)))
		{
			free(aux->value);
			aux->value = ft_strdup(new_value);
			printf("%s\n", aux->value);
		}
		aux = aux->next;
	}
	ft_print_envp_list(envp);
}

char *find_env(t_envp **envp, char *find)
{
	t_envp *aux;
		
	aux = *envp;
	while (aux ->next)
	{
		if (!ft_strncmp(aux->id, find, ft_strlen(find)))
			return (aux->value);
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
	printf("env -> %s\n", find_env(envp, "PWD="));
	printf("env -> %s\n", find_env(envp, "OLDPWD="));
	printf("PWD -> %s\n", pwd);
	printf("OLD -> %s\n", oldpwd);
	free(pwd);
	free(oldpwd);
}
