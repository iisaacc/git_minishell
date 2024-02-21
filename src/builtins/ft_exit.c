/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carmarqu <carmarqu@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 11:32:01 by carmarqu          #+#    #+#             */
/*   Updated: 2024/02/19 16:18:32 by carmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_exit(char **cmd)
{
	if (cmd[1] && cmd[2])
	{
		ft_putstr_fd("bash: exit: too many arguments", 2);
		g_status = 1;
		return ;
	}
	if (cmd[1])
	{
		if (ft_atoi(cmd[1]) != 0)
		{
			g_status = ft_atoi(cmd[1]);
			exit(g_status);
		}
		else
		{
			ft_perror_mod("exit", "numeric argument required", 2);
			exit(g_status);
		}
	}
	else
		exit(g_status);
}
