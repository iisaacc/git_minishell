/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carmarqu <carmarqu@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 13:43:29 by carmarqu          #+#    #+#             */
/*   Updated: 2024/02/06 12:40:09 by carmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_env(int fd, t_envp **envp_list)//no actualiza PWD y OLDPWD cuando hace env
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

void	ft_pwd(int fd)
{
	char buffer[1024];
	char *pwd;
	
	pwd = ft_strdup(getcwd(buffer, sizeof(buffer)));
	while (*pwd)
	{
		write(fd, &(*pwd), 1);
		pwd++;
	}
	write(fd, "\n", 1);
	free(pwd);
}

void	ft_exit(char **cmd)
{
	//printf("%s\n", cmd[0]);
	if (cmd[1])
		return ;
	if (cmd[0])
		exit(ft_atoi(cmd[0]));
	else
		exit(0);//esta con 0 pero debe ser la variable global
}

int		ft_builtins(t_envp **envp_list, t_mini *mini)//hacer como un filtro para saber se es un builtin y cual es
{
	if (!mini || !mini->full_cmd)
		return (0);//hacer con que las funciones devuelvam -1 si hay error
	else if (!ft_strncmp(mini->full_cmd[0], "echo", 5))
		return (ft_echo(mini->full_cmd, mini->outfile), 1);
	else if (!ft_strncmp(mini->full_cmd[0], "cd", 3))
		return (ft_cd(mini, envp_list), 1);//puede cambiar solo enel processo hijo, y por eso no imprime la diferencia
	else if (!ft_strncmp(mini->full_cmd[0], "pwd", 4))
		return (ft_pwd(mini->outfile), 1);
	else if (!ft_strncmp(mini->full_cmd[0], "export", 7))
		return (ft_export(envp_list, &mini->full_cmd[1]), 1);
	else if (!ft_strncmp(mini->full_cmd[0], "env", 4))
		return (ft_env(mini->outfile, envp_list), 1);
	else if (!ft_strncmp(mini->full_cmd[0], "unset", 6))
		return (ft_unset(envp_list, &mini->full_cmd[1]), 1);
	else if(!ft_strncmp(mini->full_cmd[0], "exit", 4))
		return (ft_exit(&mini->full_cmd[1]), 1);
	else
		return (0);
}