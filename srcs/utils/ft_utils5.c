/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils5.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiraldi <egiraldi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 08:59:24 by egiraldi          #+#    #+#             */
/*   Updated: 2023/02/27 12:47:32 by egiraldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

size_t	ft_replace_in_string(char *s, char c_replace, char c_with)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		if (*s == c_replace)
		{
			*s = c_with;
			count++;
		}
		s++;
	}
	return (count);
}

void	ft_clear_child_data(t_data *data, \
		char **envp, char **argv, char *cmd_path)
{
	ft_free_char_array(envp);
	ft_free_char_array(argv);
	ft_delete_list(&data->envp);
	ft_delete_cmd(&data->c_line);
	ft_sfree((void *) data->pwd);
	ft_sfree((void *) cmd_path);
	ft_sfree((void *) data->r_line);
}

int	ft_free_and_ret(char *cmd_path)
{
	ft_sfree(cmd_path);
	return (1);
}

t_return	ft_cd_error_argc(t_command *cmd)
{
	ft_err_cd_tooarg(cmd);
	return (RETURN_ERROR);
}
