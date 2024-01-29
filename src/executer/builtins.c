/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carmarqu <carmarqu@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 13:43:29 by carmarqu          #+#    #+#             */
/*   Updated: 2024/01/29 16:44:30 by carmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void ft_print_envp_list(t_envp **envp)
{
	t_envp	*tmp;

	tmp = *envp;
	while (tmp != NULL)
	{
		printf("%s\n", tmp->id);
		printf("value: %s\n", tmp->value);
		tmp = tmp->next;
	}
}

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

void	ft_echo(char **cmd, int fd)
{
	int x;
	int i;
	int flag;

	x = 1;
	flag = 0;
	if (cmd[1] && !ft_strncmp(cmd[1], "-n", 2))
	{
		flag = 1;
		x = 2;
	}
	while (cmd[x])
	{
		i = 0;
		while(cmd[x][i])
		{
			write(fd, &cmd[x][i], 1);
			i++;	
		}
		write(fd, " ", 1);
		x++;
	}
	if (!flag || cmd[1] == 0)
		write(fd, "\n", 1);
}


void	ft_env(int fd, t_envp **envp_list)
{
	int i;
	t_envp *aux;

	aux = *envp_list;
	while (aux != NULL)
	{
		i = 0;
		while (aux->id[i])
		{
			write(fd, &aux->id[i], 1);
			i++;
		}
		i = 0;
		while (aux->value[i])
		{
			write(fd, &aux->value[i], 1);
			i++;
		}
		write(fd, "\n", 1);
		aux = aux->next;
	}
}

int		ft_builtins(t_envp **envp_list, t_mini *mini)//hacer como un filtro para saber se es un builtin y cual es
{
	if (!mini || !mini->full_cmd)
		return (0);
	else if (!ft_strncmp(mini->full_cmd[0], "echo", ft_strlen(mini->full_cmd[0])))
		return (ft_echo(mini->full_cmd, mini->outfile), 1);
	else if (!ft_strncmp(mini->full_cmd[0], "env", ft_strlen(mini->full_cmd[0])))
		return (ft_env(mini->outfile, envp_list), 1);
	else if (!ft_strncmp(mini->full_cmd[0], "cd", ft_strlen(mini->full_cmd[0])))
		return (ft_cd(mini, envp_list), 1);
	else
		return (0);
}