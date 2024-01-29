/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carmarqu <carmarqu@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 13:43:29 by carmarqu          #+#    #+#             */
/*   Updated: 2024/01/29 14:08:36 by carmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	find_env(char **envp, char *find)
{
	int x;
	
	x = 0;
	while (envp[x])
	{
		if (!ft_strncmp(envp[x], find, ft_strlen(find)))
			return (x);
		x++;
	}
	return (0);
}

void	ft_cd(t_mini *mini)//se llega hasta aqui full_cmd[1] sera el camino
{
	char *opwd;
	char *pwd;
	char *oldpwd;
	char buffer[1024];
	
	opwd = ft_strdup("OLDPWD=");
 	pwd = ft_strdup("PWD=");
	oldpwd = ft_substr(mini->envp[find_env(mini->envp, "PWD=")], 4, ft_strlen(mini->envp[find_env(mini->envp, "PWD=")]) - 4);
	opwd = ft_strjoin(opwd, oldpwd);
	mini->envp[find_env(mini->envp, "OLDPWD=")] = ft_strdup(opwd);
	if (chdir(mini->full_cmd[1])) //devuleve 1 se falla
		return (free(pwd), free(opwd), free(oldpwd));
	pwd = ft_strjoin(pwd, getcwd(buffer, sizeof(buffer)));
	mini->envp[find_env(mini->envp, "PWD=")] = ft_strdup(pwd);
	printf("%s\n", mini->envp[find_env(mini->envp, "PWD=")]);
	printf("%s\n", mini->envp[find_env(mini->envp, "OLDPWD=")]);
	printf("PWD -> %s\n", pwd);
	printf("OLD -> %s\n", opwd);
	free(opwd);
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


void	ft_env(t_mini *mini, int fd)
{
	int x;
	int i;

	x = 0;
	while (mini->envp[x])
	{
		i = 0;
		while(mini->envp[x][i])
		{
			write(fd, &mini->envp[x][i], 1);
			i++;	
		}
		write(fd, "\n", 1);
		x++;
	}
}

int		ft_builtins(t_envp **envp_list, t_mini *mini)//hacer como un filtro para saber se es un builtin y cual es
{
	if (!mini || !mini->full_cmd)
		return (0);	
	else if (!ft_strncmp(mini->full_cmd[0], "echo", ft_strlen(mini->full_cmd[0])))
		ft_echo(mini->full_cmd, mini->outfile);
	else if (!ft_strncmp(mini->full_cmd[0], "cd", ft_strlen(mini->full_cmd[0])))
		ft_cd(mini);
	else if (!ft_strncmp(mini->full_cmd[0], "env", ft_strlen(mini->full_cmd[0])))
		ft_env(mini, mini->outfile);
	return (1);
}