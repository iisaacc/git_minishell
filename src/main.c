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

void ft_print_list(t_lexer **lexer)
{
	int		x;
	t_lexer	*tmp;

	tmp = *lexer;
	x = 0;
	while (tmp != NULL)
	{
		printf("word: %s\n", tmp->word);
		printf("id: %d\n", tmp->id);
		printf("type: %d\n\n", tmp->type);
		
		tmp = tmp->next;
		x++;
	}
}

int	main(int argc, char **argv)
{
	char	*input;
	t_lexer	*lexer;
	//char	*str = "echo hola >> infile que tal irmano | wc -l >>outfile";

	lexer= NULL;
	//ft_lexer(&lexer, str);
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
		ft_lexer(&lexer, input);
		ft_parser(&lexer);
		//ft_print_split(ft_lexer(input));
		ft_print_list(&lexer);
	}
	clear_history();
}