/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isporras <isporras@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 11:52:20 by isporras          #+#    #+#             */
/*   Updated: 2024/01/31 13:05:54 by isporras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_set_io(t_mini **mini, t_lexer **lexer)
{
	int		i;
	int		lap;
	int		flag;
	t_lexer	*aux;
	t_mini	*m_node;

	flag = 0;//no falla
	m_node = *mini;
	lap = 0;
	while (m_node)
	{
		i = 0;
		aux = *lexer;
		while (aux)
		{
			if (aux->type == PIPE)
				i++;
			if (aux->type == LESS && i == lap)
			{
				m_node->infile = open((aux->next)->word, O_RDONLY);
				flag += ft_file_error(m_node->infile, (aux->next)->word);//Comprueba si ha fallado open
			}
			else if (aux->type == GREATER && i == lap)
			{
				m_node->outfile = open((aux->next)->word, O_WRONLY | O_CREAT | O_TRUNC, 0644);
				flag += ft_file_error(m_node->outfile, (aux->next)->word);
			}
			aux = aux->next;
		}
		m_node = m_node->next;
		lap++;
	}
	return (flag);
}

void	ft_error(char *error, char *boole, int errint)
{
	if (!boole)
	{
		errno = errint;
		perror(error);
	}
}

char	**ft_full_cmnd(t_lexer *lexer)
{
	t_lexer	*aux;
	char	**full_cmnd;
	int		i;

	i = 1;
	aux = lexer;
	while (aux->next && (aux->next->type == FLAG || aux->next->type == STRING))
	{
		aux = aux->next;
		i++;
	}
	full_cmnd = malloc(sizeof(char *) * (i + 1));
	i = 0;
	aux = lexer;
	full_cmnd[i++] = ft_strdup(aux->word);
	while (aux->next && (aux->next->type == FLAG || aux->next->type == STRING))
	{
		aux = aux->next;
		full_cmnd[i++] = ft_strdup(aux->word);
	}
	full_cmnd[i] = NULL;
	return (full_cmnd);
}

int	ft_parser(t_lexer **lexer, t_mini **mini, char **envp, t_envp **envp_list)
{
	ft_types(lexer);
	mini = ft_to_mini_lst(lexer, mini, envp_list);
	if (ft_set_io(mini, lexer) > 0)
		return (1);
	if (ft_set_path_cmnd(mini, lexer, envp) == 1)
		return (1);
	return (0);
}
