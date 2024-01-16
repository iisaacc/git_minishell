/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carmarqu <carmarqu@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 12:00:49 by carmarqu          #+#    #+#             */
/*   Updated: 2024/01/16 14:31:35 by carmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	lexer(char *input)
{
	int x;//char[]
	int i;//char[][]
	int lw;//fin de palavra
	char **split = NULL;
	char c;

	x = 0;
	i = 0;
	while (input[i] == ' ')
		i++;
	while (input[i])
	{
		lw = i;
		if (input[i] == ' ' || input[i] == '\'' || input[i] == '"')
		{
			printf("aqui\n");
			c = input[i++];
			while(input[i] != c && input[i])
				i++;
			split[x] = ft_substr(input, 0, (i - lw));
			x++;
			
		}	
		i++;
	}
	x = 0;
	while (split[x])
		printf("%s", split[x++]);
}