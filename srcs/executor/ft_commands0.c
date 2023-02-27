/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_commands0.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiraldi <egiraldi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 08:59:51 by egiraldi          #+#    #+#             */
/*   Updated: 2023/02/27 09:10:27 by egiraldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_command	*ft_create_cmd_elem(void)
{
	t_command	*output;

	output = (t_command *) ft_malloc(sizeof(t_command));
	if (!output)
		return (NULL);
	ft_memset((void *) output, 0, sizeof(t_command));
	output->fd = (t_fd *) ft_malloc(sizeof(t_fd));
	if (!output->fd)
		return (NULL);
	output->fd->in = STDIN_FILENO;
	output->fd->out = STDOUT_FILENO;
	output->fd->err = STDERR_FILENO;
	output->result = RETURN_FALSE;
	output->re = NULL;
	return (output);
}

void	ft_delete_cmd(t_command **commands)
{
	t_command	*tmp;

	while (*commands)
	{
		tmp = *commands;
		*commands = (*commands)->next;
		ft_sfree((void *) tmp->cmd);
		ft_sfree((void *) tmp->fd);
		tmp->fd = NULL;
		tmp->cmd = NULL;
		ft_delete_list(&tmp->argv);
		ft_lstdel_re(&tmp->re);
		ft_sfree((void *) tmp);
		tmp = NULL;
	}
}

int	ft_build_in_exe(t_command *cmd, t_data *data)
{
	if (ft_strcmp(cmd->cmd, "exit"))
		return (ft_exit(cmd, data));
	else if (ft_strcmp(cmd->cmd, "pwd"))
		return (ft_pwd(data, cmd));
	else if (ft_strcmp(cmd->cmd, "env"))
		return (ft_env(data, cmd));
	else if (ft_strcmp(cmd->cmd, "export"))
		return (ft_export(data, cmd));
	else if (ft_strcmp(cmd->cmd, "unset"))
		return (ft_unset(data, cmd));
	else if (ft_strcmp(cmd->cmd, "cd"))
		return (ft_cd(data, cmd));
	else if (ft_strcmp(cmd->cmd, "echo"))
		return (ft_echo(cmd));
	else if (ft_strcmp(cmd->cmd, "error_codes"))
		return (ft_error_codes(cmd));
	return (RETURN_FALSE);
}

void	ft_print_commands(t_command *commands)
{
	t_envp	*tmp;
	int		i;

	while (commands)
	{
		i = 0;
		tmp = commands->argv;
		while (tmp)
		{
			printf("argc=%i [%s]\n", i, tmp->var);
			tmp = tmp->next;
			i++;
		}
		if (commands)
			commands = commands->next;
	}
}
