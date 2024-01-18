/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carmarqu <carmarqu@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 07:26:35 by carmarqu          #+#    #+#             */
/*   Updated: 2024/01/17 16:47:33 by carmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <fcntl.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "includes/libft/libft.h"

# define CMND 1
# define FLAG 2
# define STRING 3
# define FILE 4
# define TOKEN 5

//int	g_status; variavel global

typedef struct s_lexer
{
	char *word; //palavra
	//int tokens; //cantidad de tokens
	//char **args; //args
	int type; //1-> func, 2->flags, 3->string, 4->files 5->token
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

typedef struct s_redir
{
	int	tmpin;
	int	tmpout;
	int	fork;
	int	fdin;
	int	fdout;
	int	fdpipe[2];
}		t_redir;

char		**ft_lexer(char *input);
void		ft_extend_var(char **lexer);
char		**ft_split_lexer(char const *s, char c);
void		create_nodes(t_lexer **lexer, char **input);
void		ft_print_list(t_lexer *lexer);
void		free_node(t_lexer **node);
void		ft_types(t_lexer *lexer);
char		**ft_get_tokens(char **lexer);
char const	*ft_check_quotes(char const *s);

#endif