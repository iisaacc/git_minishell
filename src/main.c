/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carmarqu <carmarqu@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:19:24 by carmarqu          #+#    #+#             */
/*   Updated: 2024/01/16 16:57:44 by carmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_countl_mod(char const *s, char c)
{
	int	i;
	int	count;
	int	b;

	b = 0;
	i = 0;
	count = 0;
	while (s && s[i] && count < 2)
	{
		if (s[i] != c && b == 0 && count < 2)
		{
			count++;
			b = 1;
		}
		if (s[i] == c)
			b = 0;
		i++;
	}
	return (count);
}

char	**ft_splitaux_mod(char **str, char *s, char c)
{
	int		i;
	int		len;
	int		lap;

	lap = 0;
	i = 0;
	while (s && s[i])
	{
		len = 0;
		while (s[i + len] != c && s[i + len] != '\0')
			len++;
		if (len > 0)
			ft_to2d(&s[i], len, str, lap++);
		i += len;
		c = '\0';
		if (s[i] != '\0')
			i++;
	}
	str[lap] = NULL;
	return (str);
}

char	**ft_split_mod(char const *s, char c)
{
	char	**ans;

	ans = (char **)malloc((ft_countl_mod(s, c) + 1) * sizeof(char *));
	if (!ans)
		return (NULL);
	return (ft_splitaux_mod(ans, (char *)s, c));
}

int	main(int argc, char **argv)
{
	char *input;
	
	argv = 0;
	
	if (argc > 1)
	{
		printf("Wrong number of arguments\n");
		return (1);
	}
	while((input = readline("Minishell>")))
	{
		add_history(input);
		//lexer(input);
		ft_split_mod(input, ' ');
		printf("%s\n", input);
		//rl_replace_line(" ", 0);
	}
	clear_history();
}