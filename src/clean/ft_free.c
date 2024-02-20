/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isporras <isporras@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 13:32:05 by isporras          #+#    #+#             */
/*   Updated: 2024/02/20 13:32:05 by isporras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	final_free(char *input, t_envp **envp)
{
	ft_free_envp_list(envp);
	free(input);
	clear_history();
}

void	ft_clean_log(char *log, char *input, char **split_input)
{
	free(log);
	free(input);
	ft_free_2d(split_input);
}
