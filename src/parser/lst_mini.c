/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_mini.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isporras <isporras@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 11:59:30 by isporras          #+#    #+#             */
/*   Updated: 2024/01/22 11:59:30 by isporras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_mini	*ft_mini_new(t_lexer *lexer, char **envp)
{
	t_mini	*mini;

	mini = malloc(sizeof(t_mini));
	mini->full_cmd = ft_full_cmnd(lexer);
	mini->full_path = ft_find_cmnd_path(envp, lexer->word);
	mini->infile = STDIN_FILENO;
	mini->outfile = STDOUT_FILENO;
	mini->next = NULL;
	return (mini);
}

t_mini	*mini_last_list(t_mini *mini)//va hasta el final de la lista
{
	if (!mini)
		return (0);
	while (mini->next != 0)
		mini = mini->next;
	return (mini);
}

void	mini_add_new(t_mini **mini, t_mini *new)//añande un nodo a la lista
{
	t_mini	*aux;

	if (!new)
		return ;
	if (!*mini)
	{
		*mini = new;
		return ;
	}
	aux = mini_last_list(*mini);
	aux->next = new;
}

t_mini	**ft_to_mini_lst(t_lexer **lexer, t_mini **mini, char **envp)
{
	t_lexer	*aux;

	aux = *lexer;
	while (aux)
	{
		if (aux->type == CMND)
			mini_add_new(mini, ft_mini_new(aux, envp));
		aux = aux->next;
	}
	return (mini);
}