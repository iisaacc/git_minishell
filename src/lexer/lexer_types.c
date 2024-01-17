/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_types.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carmarqu <carmarqu@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 15:13:24 by carmarqu          #+#    #+#             */
/*   Updated: 2024/01/17 16:50:37 by carmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_subtypes()
{
	
} 

void	ft_types(t_lexer *lexer)
{
	t_lexer *aux;
	int flag; //flag para saver quando tem um pipe
	
	flag = 1;
	aux = lexer;
	while (aux)
	{
		if (flag == 1)
		{
			aux->type = 1;//es una funcion
			flag--;
		}
		else if (aux->word[0] == '-')//es una flag
			aux->type = 2;
		else if (aux->word[0] == '|' || aux->word[0] == '<' || aux->word[0] == '>')//es um token
		{
			if (aux->word[0] == '|' )
				flag++;
			aux->type = 5;
		}
		aux = aux->next;
	}
}