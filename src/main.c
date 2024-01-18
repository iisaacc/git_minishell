/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carmarqu <carmarqu@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:19:24 by carmarqu          #+#    #+#             */
/*   Updated: 2024/01/18 17:29:24 by carmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_print_list(t_lexer *lexer)
{
	int x;
	
	x = 0;
	while (lexer != NULL)
	{
		printf("word: %s\n", lexer->word);
		printf("id: %d\n", lexer->id);
		printf("type: %d\n\n", lexer->type);
		
		lexer = lexer->next;
		x++;
	}
}

int	main(int argc, char **argv)
{
	char	*input;
	t_lexer	*lexer;
	//"echo> \"hhh $HOM ffff\" hello      there\" $USER how are \'you \'doing?  \"  |wc  \" -l >>outfile";
	//create_nodes(&lexer, ft_lexer(input));
	lexer= NULL;
	if (argc > 1 && argv)
	{
		printf("Wrong number of arguments\n");
		return (1);
	}
	while((input = readline("Minishell>")))
	{
		if (!ft_check_quotes(input))
			return (write(2, "quotes\n", 8), 1);
		add_history(input);
		create_nodes(&lexer, ft_lexer(input));
		//ft_print_split(ft_lexer(input));
		ft_types(lexer);
		ft_print_list(lexer);
	}
	clear_history();
}