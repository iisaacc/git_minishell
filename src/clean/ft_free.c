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
	if (input)
		free(input);
	clear_history();
}

void	ft_clean_log(t_main *m)
{
	free(m->log);
	m->log = NULL;
	free(m->input);
	m->input = NULL;
	ft_free_2d(m->split_input);
	m->split_input = NULL;
}
