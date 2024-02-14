/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carmarqu <carmarqu@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:19:24 by carmarqu          #+#    #+#             */
/*   Updated: 2024/02/13 12:41:58 by carmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int last_status;

void	ft_print_mini_lst(t_mini **mini)
{
	t_mini	*tmp;

	tmp = *mini;
	while (tmp != NULL)
	{
		printf("cmd:\n");
		ft_print_split(tmp->full_cmd);
		printf("total cmds: %d\n", tmp->total_cmnds);
		printf("id: %d\n", tmp->id);
		printf("path: %s\n", tmp->full_path);
		printf("infile fd: %d\n", tmp->infile);
		printf("outfile fd: %d\n\n", tmp->outfile);
		tmp = tmp->next;
	}
}

void	ft_print_list(t_lexer **lexer)
{
	t_lexer	*tmp;

	tmp = *lexer;
	while (tmp)
	{
		printf("word: %s\n", tmp->word);
		printf("id: %d\n", tmp->id);
		printf("type: %d\n\n", tmp->type);
		tmp = tmp->next;
	}
}

void	final_free (char *log, t_envp **envp)
{
	ft_free_envp_list(envp);//hay que quedar fuera del bucle
	free(log);
}

int	main(int argc, char **argv, char **envp)
{
	t_main	m;

	m.envp_list = NULL;
	m.lexer = NULL;
	m.mini = NULL;
	last_status = 0;
	if (argc > 1 && argv)
		return (printf("Wrong number of arguments\n"), 1);
	ft_init_var(envp, &m.envp_list);
	singal_init();
	while ((m.input = readline(ft_refresh_log())))//lee la línea
	{
		ft_quotes_input(&m.input);
		if (ft_strncmp(m.input, "\0", 1) != 0)//si esta vacio no adiciona al historial
			add_history(m.input);
		if (ft_lexer(&m.lexer, m.input) != NULL)//crea la lista de tokens
		{
			if (ft_parser(&m.lexer, &m.mini, envp, &m.envp_list) == -1)
				last_status = ft_executer(&m.mini);
		}
		ft_free_lsts(&m.lexer, &m.mini);
	}
	//final_free(input, log, &m.envp_list);
	clear_history();
}
