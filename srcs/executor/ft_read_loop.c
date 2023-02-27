/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiraldi <egiraldi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 09:00:00 by egiraldi          #+#    #+#             */
/*   Updated: 2023/02/27 09:10:27 by egiraldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_read_loop(t_data *data)
{
	while (1)
	{
		data->r_line = readline(PROMPT);
		if (data->r_line == NULL)
			break ;
		if (ft_strlen(data->r_line) > 0)
			add_history(data->r_line);
		if (ft_parser(data))
			continue ;
		if ((ft_do_valid_redirections(data) == RETURN_SUCCESS)
			&& (ft_cycle_cmd(data) == RETURN_EXIT))
			break ;
		ft_wait_for_kids(data);
		ft_sfree((void *) data->r_line);
		ft_delete_cmd(&data->c_line);
	}
	return (0);
}

int	ft_cycle_cmd(t_data *data)
{
	t_command	*cmd;
	int			result;

	ft_set_parent_active();
	cmd = data->c_line;
	while (cmd)
	{
		if (cmd->result == RETURN_SUCCESS && cmd->cmd)
		{
			if (cmd->next)
				ft_create_pipe(cmd);
			result = ft_build_in_exe(cmd, data);
			if (result == RETURN_EXIT)
				return (RETURN_EXIT);
			if (result == RETURN_FALSE)
				ft_do_execve(cmd, data);
		}
		else if (cmd->result == RETURN_SUCCESS && !cmd->cmd)
			return (ft_print_error(cmd, ERR_SYNTAX, ""));
		ft_close_pipe(cmd);
		cmd = cmd->next;
	}
	return (RETURN_SUCCESS);
}

void	ft_wait_for_kids(t_data *data)
{
	t_command	*tmp;
	int			status;

	if (!data->c_line)
		return ;
	tmp = data->c_line;
	status = 0;
	while (tmp)
	{
		if (tmp->pid != 0 && waitpid(tmp->pid, &status, 0) != RETURN_ERROR)
		{
			if (WIFEXITED(status))
				tmp->errnum = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				tmp->errnum = 128 + WTERMSIG(status);
		}
		tmp = tmp->next;
	}
	tmp = ft_last_cmd(data->c_line);
	data->errnum = tmp->errnum;
	ft_set_parent_interactive();
}
