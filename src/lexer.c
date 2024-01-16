/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carmarqu <carmarqu@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 12:00:49 by carmarqu          #+#    #+#             */
/*   Updated: 2024/01/16 16:52:50 by carmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


int words_len(char *input)
{
	int i;
	int size;
	char c;
	
	size = 0;
	i = 0;
	while (input[i])
	{
		while (input[i] != ' ' && input[i] != '\'' && input[i] != '"' && input[i + 1] != '\0')
			i++;//mientras sea una palavra		
		while (input[i] == ' ' || input[i] == '\'' || input[i] == '"' || input[i + 1] == '\0')
			i++;
		size++;
		if( input[i] == '"' || input[i + 1] == '\'')
		{
			c = input[i];
			while(input[i] != c && input[i])
				i++;//busca el final de las comilas
			//size++;
		}
		i++;
	}
	printf("%d\n", size);
	return (size);
}

void	lexer(char *input)
{
	int x;//char[]
	int i;//char[][]
	int lw;//fin de palavra
	char **split;
	char c;
	int flag;
	
	//words_len(input);
	flag = 1;
	x = 0;
	i = 0;
	split = (char **)malloc(sizeof(char *) * 5);
	while (input[i] == ' ')
		i++;
	while (x < 4)
	{
		if (input[i] == ' ' || input[i] == '\'' || input[i] == '"' || input[i + 1] == '\0')
		{
			if (flag == 1)//si es el primer "split"
			{
				split[x++] = ft_substr(input, 0, i);
				flag--;
				lw = i;
			}
			c = input[i++];
			while (input[i] == c)
				i++;
			if (input[i] == '"' || input[i + 1] == '\0')//checkea si el separador va a ser espacio o si hay comillas
				c = input[i];
			printf("c = %c\n", c);
			while(input[i + 1] != c && input[i + 1] != '\0')//len de la palabra
				i++;
			split[x] = ft_substr(input, lw + 1, (i - lw) + 1);//hace el split
			lw = i + 1;
			x++;
		}	
		i++;
	}
	x = 0;
	while (x < 4)
	{
		printf("%s\n", split[x]);
		x++;
	}
}
