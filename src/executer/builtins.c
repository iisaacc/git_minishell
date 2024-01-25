/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carmarqu <carmarqu@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 13:43:29 by carmarqu          #+#    #+#             */
/*   Updated: 2024/01/25 16:39:12 by carmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_echo(char **cmd, int fd)
{
	int x;
	int i;
	int flag;

	x = 1;
	flag = 0;
	if (!ft_strncmp(cmd[1], "-n", 2))
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
	if (!flag)
		write(fd, "\n", 1);
}

int		ft_builtins(t_mini *mini)//hacer como un filtro para saber se es un builtin y cual es
{	
	int len;

	len = ft_strlen(mini->full_cmd[0]);
	if (!ft_strncmp(mini->full_cmd[0], "echo", len))
		ft_echo(mini->full_cmd, mini->outfile);
	if (mini->next)
		ft_builtins(mini->next);
	return (1);
}