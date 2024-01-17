/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isporras <isporras@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 07:26:35 by carmarqu          #+#    #+#             */
/*   Updated: 2024/01/17 14:14:21 by isporras         ###   ########.fr       */
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

typedef struct s_lexer
{
	char *word; //palavra
	//int tokens; //cantidad de tokens
	//char **args; //args
	int type; //1-> func, 2->tokens, 3->string, 4->files
	int id; //pos en la lista
	struct s_lexer *next;//puntero al siguiente nodo

}		t_lexer;

typedef struct s_prompt
{
	t_lexer	*cmds;//lista enlazada con los comandos
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

/* typedef struct s_simple_cmds
{
	char                    **str;
	//int                     (*builtin)(t_tools *, struct s_simple_cmds *);
	int                     num_redirections;
	char                    *hd_file_name;
	t_lexer                 *redirections;
	struct s_simple_cmds	*next;
	struct s_simple_cmds	*prev;
}	t_simple_cmds;  */

char	**ft_lexer(char *input);
void	ft_extend_var(char **lexer);
char	**ft_split_lexer(char const *s, char c);

#endif