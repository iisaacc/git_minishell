/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carmarqu <carmarqu@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 13:39:10 by carmarqu          #+#    #+#             */
/*   Updated: 2024/02/07 12:48:03 by carmarqu         ###   ########.fr       */
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

void	unset_error(char *str)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd("cd: ", 2);
	ft_putchar_fd('`', 2);
	ft_putstr_fd(str, 2);
	ft_putchar_fd('\'', 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd("not a valid identifier\n", 2);
}

void ft_unset(t_envp **envp, char **args)
{
	t_envp *aux;
	int x;
	char *id;
	
	x = 0;
	while (args[x])
	{
		if(!ft_strchr(args[x], '='))	
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
		}
		else
			unset_error(args[x]);
		x++;
	}
}