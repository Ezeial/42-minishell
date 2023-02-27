/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiraldi <egiraldi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 08:58:57 by egiraldi          #+#    #+#             */
/*   Updated: 2023/02/27 14:07:43 by egiraldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_data	*g_data;

static int	ft_set_pwd(t_data *data)
{
	char	*output;

	output = (char *) ft_malloc(BUFFER_SIZE);
	if (!output)
		return (1);
	getcwd(output, BUFFER_SIZE);
	output = ft_realloc("PWD=", output, 0, 1);
	if (!output)
		return (1);
	data->pwd = output;
	if (ft_change_envp(data, output))
		return (1);
	return (0);
}

static int	ft_initialize(t_data *data, char **envp)
{
	t_envp	*tmp_envp;

	data->gclst = 0;
	data->c_line = NULL;
	data->r_line = NULL;
	data->errnum = 0;
	data->envp = 0;
	if (envp && *envp)
		data->envp = ft_copy_envp(envp);
	tmp_envp = ft_get_envp_element(data->envp, "PATH");
	if (!tmp_envp)
		ft_change_envp(data, DEFAULT_PATH);
	tmp_envp = ft_get_envp_element(data->envp, "PWD");
	ft_init_shell_level(data);
	if (!tmp_envp)
		ft_set_pwd(data);
	else
	{
		data->pwd = ft_string_dup(tmp_envp->var);
		if (!(data->pwd))
			return (1);
	}
	return (ft_change_envp(data, "SHELL=EZIO & MARC MINISHELL!"));
}

void	ft_clear_mem(t_data *data)
{
	t_command	*tmp;

	ft_delete_list(&data->envp);
	if (data->c_line)
	{
		tmp = ft_last_cmd(data->c_line);
		data->errnum = tmp->errnum;
		ft_delete_cmd(&data->c_line);
	}
	rl_clear_history();
	ft_sfree((void *) data->pwd);
	if (data->r_line)
		ft_sfree((void *) data->r_line);
	else
		ft_write_fd(STDOUT_FILENO, "exit\n");
	ft_plst_free(&(data->gclst));
}

int	main(int argc, char **argv, char **envp)
{
	t_data		data;

	(void) argc;
	(void) argv;
	g_data = &data;
	if (!ft_initialize(&data, envp))
	{
		ft_set_parent_interactive();
		ft_read_loop(&data);
	}
	else
	{
		ft_write_fd(STDERR_FILENO, "Allocation error.\n");
		data.errnum = 1;
	}
	ft_clear_mem(&data);
	return (data.errnum);
}
