/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_mini.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carmarqu <carmarqu@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 14:13:15 by carmarqu          #+#    #+#             */
/*   Updated: 2024/01/30 14:46:07 by carmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_total_cmnds(t_mini **mini, int total_cmnds)
{
	int		i;
	t_mini	*aux;

	aux = *mini;
	i = 0;
	while (i < total_cmnds && aux)
	{
		aux->total_cmnds = total_cmnds;
		aux = aux->next;
		i++;
	}
}

t_mini	*ft_mini_new(t_lexer *l_node, char **envp, t_lexer **lexer, int lap, t_envp **envp_list)
{
	t_mini	*mini;

	mini = malloc(sizeof(t_mini));
	mini->full_cmd = ft_full_cmnd(l_node);
	mini->full_path = ft_find_cmnd_path(envp, l_node->word);
	ft_cmnd_error(l_node->word, mini->full_path);
	mini->infile = STDIN_FILENO;
	mini->outfile = STDOUT_FILENO;
	mini->id = lap;
	mini->envp = envp_list;
	mini->next = NULL;
	ft_set_io(mini, lexer, lap);
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

t_mini	**ft_to_mini_lst(t_lexer **lexer, t_mini **mini, char **envp, t_envp **envp_list)
{
	t_lexer	*aux;
	int		lap;

	lap = 0;
	aux = *lexer;
	while (aux)
	{
		if (aux->type == PIPE)
			lap++;
		if (aux->type == CMND)
			mini_add_new(mini, ft_mini_new(aux, envp, lexer, lap, envp_list));
		aux = aux->next;
	}
	ft_total_cmnds(mini, lap + 1);
	//ft_print_list(lexer);
	return (mini);
}
