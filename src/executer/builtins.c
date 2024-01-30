/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carmarqu <carmarqu@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 13:43:29 by carmarqu          #+#    #+#             */
/*   Updated: 2024/01/30 15:02:48 by carmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_echo(char **cmd, int fd)//hay cosas que cambiar
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
	if (!flag || cmd[2] != 0)//puede haber problemas con las flags
		write(fd, "\n", 1);
}


void	ft_env(int fd, t_envp **envp_list)//no actualiza PWD y OLDPWD
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
	ft_strdup(getcwd(buffer, sizeof(buffer)));
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
		return (ft_cd(mini, envp_list), 1);//puede cambiar solo enel processo hijo, y por eso no imprime la diferencia
	else if (!ft_strncmp(mini->full_cmd[0], "pwd", ft_strlen(mini->full_cmd[0])))
		return (ft_pwd)
	else
		return (0);
}