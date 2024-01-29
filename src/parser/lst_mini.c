/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_mini.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carmarqu <carmarqu@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 14:13:15 by carmarqu          #+#    #+#             */
/*   Updated: 2024/01/29 13:40:47 by carmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_total_cmnds(t_mini **mini, int total_cmnds)
{
	int		i;
	t_mini	*aux;
	
	aux = *mini;
	i = 0;
	while (i < total_cmnds)
	{
		aux->total_cmnds = total_cmnds;
		aux = aux->next;
		i++;
	}
}

void	ft_free_mini_lst(t_mini **mini)
{
	t_mini	*aux;

	while (*mini)
	{
		aux = (*mini)->next;
		ft_free_2d((*mini)->full_cmd);
		if ((*mini)->full_path != NULL)
			free((*mini)->full_path);
		/* if ((*mini)->envp[find_env((*mini)->envp, "PWD=")])
		{
			free((*mini)->envp[find_env((*mini)->envp, "PWD=")]);
			free((*mini)->envp[find_env((*mini)->envp, "OLDPWD=")]);
		} */
		free(*mini);
		*mini = aux;
	}
	*mini = NULL;
}

t_mini	*ft_mini_new(t_lexer *l_node, char **envp, t_lexer **lexer, int lap)
{
	t_mini	*mini;

	mini = malloc(sizeof(t_mini));
	mini->full_cmd = ft_full_cmnd(l_node);
	mini->full_path = ft_find_cmnd_path(envp, l_node->word);
	ft_cmnd_error(l_node->word, mini->full_path);
	mini->infile = STDIN_FILENO;
	mini->outfile = STDOUT_FILENO;
	mini->envp = envp;
	mini->id = lap;
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

t_mini	**ft_to_mini_lst(t_lexer **lexer, t_mini **mini, char **envp)
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
			mini_add_new(mini, ft_mini_new(aux, envp, lexer, lap));
		aux = aux->next;
	}
	ft_total_cmnds(mini, lap + 1);
	return (mini);
}
