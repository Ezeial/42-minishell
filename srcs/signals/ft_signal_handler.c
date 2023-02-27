/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiraldi <egiraldi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 08:59:29 by egiraldi          #+#    #+#             */
/*   Updated: 2023/02/27 09:10:27 by egiraldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_parent_sigterm(int sign)
{
	if (sign == SIGTERM)
	{
		write(1, "exit\n", 5);
		ft_clear_mem(g_data);
		exit(0);
	}
}

void	ft_parent_interactive_sigint(int sign)
{
	if (sign == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_data->errnum = 130;
	}
}

void	ft_parent_active_sigint(int sign)
{
	if (sign == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
	}
}

void	ft_parent_active_sigquit(int sign)
{
	if (sign == SIGQUIT)
	{
		ft_write_fd(1, "Quit\n");
	}
}
