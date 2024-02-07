/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carmarqu <carmarqu@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 13:43:29 by carmarqu          #+#    #+#             */
/*   Updated: 2024/02/07 14:18:51 by carmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int		ft_builtins(t_envp **envp_list, t_mini *mini)//hacer como un filtro para saber se es un builtin y cual es
{
	if (!mini || !mini->full_cmd)
		return (0);//hacer con que las funciones devuelvam -1 si hay error
	else if (!ft_strncmp(mini->full_cmd[0], "echo", 5))
		return (ft_echo(mini->full_cmd, mini->outfile), 1);
	else if (!ft_strncmp(mini->full_cmd[0], "cd", 3))
		return (ft_cd(mini, envp_list));
	else if (!ft_strncmp(mini->full_cmd[0], "pwd", 4))
		return (ft_pwd(mini->outfile), 1);
	else if (!ft_strncmp(mini->full_cmd[0], "export", 7))
		return (ft_export(envp_list, &mini->full_cmd[1]), 1);
	else if (!ft_strncmp(mini->full_cmd[0], "env", 4))
		return (ft_env(mini->outfile, envp_list, &mini->full_cmd[1]));
	else if (!ft_strncmp(mini->full_cmd[0], "unset", 6))
		return (ft_unset(envp_list, &mini->full_cmd[1]), 1);
/* 	else if(!ft_strncmp(mini->full_cmd[0], "exit", 4))
		return (ft_exit(&mini->full_cmd[1]), 1); */
	else
		return (0);
}