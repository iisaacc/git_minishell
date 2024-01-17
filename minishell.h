/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isporras <isporras@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 07:26:35 by carmarqu          #+#    #+#             */
/*   Updated: 2024/01/17 13:26:07 by isporras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "includes/libft/libft.h"

//int	g_status; variavel global

typedef struct s_prompt
{
	t_list	*cmds;//lista enlazada con los comandos(hay que crear esa t_list)
	char	**envp;//array ** que guarda cada palavra(frase) del prompt
	pid_t	pid;//pid del processo principal
}		t_prompt;

typedef struct s_mini
{
	char	**full_cmd;//comando y sus argumentos
	char	*full_path;//camino del ejecutable si no es un builtin
	int		infile;//fd de entrada
	int		outfile;//fd de salida
}		t_mini;

void	lexer(char *input);
int		ft_count_split(char const *s);
char	**ft_split_lexer(char const *s, char c);

#endif