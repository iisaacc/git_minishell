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
	if (ft_atoi(cmd[0]) && cmd[1])
	{
		ft_putstr_fd("bash: exit: too many arguments", 2);
		last_status = 1;
		return ;
	}
	if (cmd[0])
	{
		if (ft_atoi(cmd[0]) != 0)
		{
			last_status = ft_atoi(cmd[0]);
			exit(last_status);
		}
		else
		{
			ft_perror_mod("exit", "numeric argument required", 2);
			exit(last_status);
		}
	}
	else
		exit(last_status);
}
