/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isporras <isporras@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:19:24 by carmarqu          #+#    #+#             */
/*   Updated: 2024/01/17 15:43:21 by isporras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_print_list(t_lexer *lexer)
{
	int x;

	x = 0;
	while (lexer != NULL)
	{
		printf("%s\n", lexer->word);
		printf("%d\n", lexer->id);
		lexer = lexer->next;
		x++;
	}
}

int	main(int argc, char **argv)
{
	t_lexer	*lexer;
	char	*input;

	lexer = NULL;
	if (argc > 1 && argv)
	{
		printf("Wrong number of arguments\n");
		return (1);
	}
	while((input = readline("Minishell>")))
	{
		add_history(input);
		ft_print_split(ft_lexer(input));
		//ast(&lexer, ft_lexer(input));
		//ft_print_list(lexer);
	}
	int x;
	x = 0;
	clear_history();
}