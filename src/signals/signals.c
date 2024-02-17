/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carmarqu <carmarqu@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 13:55:30 by carmarqu          #+#    #+#             */
/*   Updated: 2024/02/17 17:30:06 by carmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	signal_helper(void)
{
	rl_on_new_line();
	rl_redisplay();
	ft_putchar_fd('\n', 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	last_status = CTRL_C;
}

void	ft_sigint(int sig)
{
	(void)sig;
	if (last_status == HEREDOC || last_status == IN_CMD)
	{
		if (last_status == HEREDOC)
			ioctl(0, TIOCSTI, "\n");
		else
			ft_putchar_fd('\n', 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		last_status = EXIT_CMD;
	}
	else
		signal_helper();
}

int	singal_init(void)
{
	last_status = INIT;
	signal(SIGINT, ft_sigint);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	return (0);
}
