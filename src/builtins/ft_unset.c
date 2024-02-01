/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carmarqu <carmarqu@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 13:39:10 by carmarqu          #+#    #+#             */
/*   Updated: 2024/02/01 15:30:01 by carmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void unset_node(t_envp *aux)
{
	if (aux->next->next)
	{
		free(aux->next->id);
		free(aux->next->value);
		free(aux->next);	
		aux->next = aux->next->next;
	}
	else 
	{
		free(aux->next->id);
		free(aux->next->value);
		free(aux->next);
		aux->next = NULL;
	}
}

void ft_unset(t_envp **envp, char **args)
{
	t_envp *aux;
	int x;
	char *id;
	
	x = 0;
	while (args[x])
	{
		id = ft_strdup(args[x]);
		if (!ft_strchr(id, '='))
			id = ft_strjoin(id, "=");
		if (find_env(envp, id))
		{
			aux = *envp;
			while (aux)
			{
				if (aux->next && !ft_strncmp(aux->next->id, id, ft_strlen(id)))
					unset_node(aux);
				aux = aux->next;
			}
		}
		free(id);
		x++;
	}
}
