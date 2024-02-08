/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isporras <isporras@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 13:55:30 by carmarqu          #+#    #+#             */
/*   Updated: 2024/02/08 14:58:42 by isporras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_sigint(int sig)
{
	sig = 0;
	//rl_replace_line("", 0);
	ft_putchar_fd('\n', 0);
	rl_on_new_line();//indica al terminal que una nueva linea esta se inicializando
	rl_redisplay();//fuerza atualizacion de la linea
}

int singal_init()
{
	signal(SIGINT, ft_sigint);
	return (0);
}