/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils6.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiraldi <egiraldi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 13:24:08 by egiraldi          #+#    #+#             */
/*   Updated: 2023/02/27 14:06:08 by egiraldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

unsigned int	ft_atou(char *s)
{
	unsigned long	n;

	n = 0;
	while (*s >= '0' && *s <= '9')
	{
		n *= 10;
		n += *s++ - '0';
		if (n > INT_MAX)
		{
			ft_write_fd(STDERR_FILENO, "Parse error\n");
			ft_super_exit();
		}
	}
	if (*s)
		return (-1);
	return (n);
}

void	ft_utoa(char *o, unsigned int n)
{
	unsigned char	pow;
	unsigned int	bkp;

	pow = 0;
	bkp = n;
	o[0] = '0';
	o[1] = 0;
	while (bkp)
	{
		bkp /= 10;
		pow += 1;
	}
	if (pow)
		o[pow] = 0;
	while (pow)
	{
		o[--pow] = n % 10 + '0';
		n /= 10;
	}
}

void	ft_init_shell_level(t_data *data)
{
	char			buffer[255];
	unsigned int	shlvl;
	char			*newshlvl;

	if (!ft_get_envp_element(data->envp, "SHLVL"))
		ft_change_envp(data, "SHLVL=1");
	else
	{
		shlvl = ft_atou(ft_getenv("SHLVL", data->envp));
		shlvl += 1;
		ft_utoa(buffer, shlvl);
		newshlvl = ft_realloc("SHLVL=", buffer, 0, 0);
		ft_change_envp(data, newshlvl);
		ft_sfree(newshlvl);
	}
}
