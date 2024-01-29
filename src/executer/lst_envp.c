/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_envp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carmarqu <carmarqu@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 14:03:51 by carmarqu          #+#    #+#             */
/*   Updated: 2024/01/29 15:35:19 by carmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

t_envp	*last_list_envp(t_envp *lst)//va hasta el final de la lista
{
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	add_new_envp(t_envp **lst, t_envp *new)//añande un nodo a la lista
{
	t_envp	*aux;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	aux = last_list_envp(*lst);
	aux->next = new;
}

t_envp *envp_new(char *envp)
{
	t_envp *new;
	char **splitted;
	
	new = malloc(sizeof(t_envp));
	splitted = ft_split(envp, '=');
	new->id = ft_strdup(splitted[0]);
	new->id = ft_strjoin(new->id, "=");
	if (splitted[1] == NULL)
		new->value = ft_strdup("");
	else
		new->value = ft_strdup(splitted[1]);
	new->next = NULL;
	ft_free_2d(splitted);
	return (new);
}

void	create_envp(t_envp **envp_list, char **envp)
{
	int x;

	x = 0;
	while (envp[x])
	{
		add_new_envp(envp_list, envp_new(envp[x]));
		x++;
	}
}