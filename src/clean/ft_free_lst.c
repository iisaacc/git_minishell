/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_lst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isporras <isporras@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 11:45:41 by isporras          #+#    #+#             */
/*   Updated: 2024/01/30 12:14:27 by isporras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_free_mini_lst(t_mini *mini)
{
	t_mini	*aux;

	while (mini)
	{
		aux = mini->next;
		ft_free_2d(mini->full_cmd);
		free(mini->full_path);
		free(mini);
		mini = aux;
	}
}

void	ft_free_lexer_lst(t_lexer **node)
{
	t_lexer	*node_aux;

	//if (!node | !*node)
	//	return ;
	while (*node)
	{
		node_aux = (*node)->next;
		free((*node)->word);
		free(*node);
		*node = node_aux;
	}
	*node = NULL;
}

void	ft_free_envp_list(t_envp **envp)
{
	t_envp *aux;

	while (*envp)
	{
		aux = (*envp)->next;
		free((*envp)->id);
		free((*envp)->value);
		free(*envp);
		*envp = aux;
	}
	*envp = NULL;
}

void	ft_free_lsts(t_lexer **lexer, t_mini **mini, t_envp **envp)
{
	ft_free_lexer_lst(lexer);
	ft_free_mini_lst(*mini);
	ft_free_envp_list(envp);
}