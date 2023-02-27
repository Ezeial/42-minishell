/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executable.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiraldi <egiraldi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 08:59:56 by egiraldi          #+#    #+#             */
/*   Updated: 2023/02/27 12:17:57 by egiraldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_do_execve(t_command *cmd, t_data *data)
{
	char	**paths;
	char	*cmd_path;
	char	*tmp;

	paths = ft_split(ft_getenv("PATH", data->envp), ':');
	if (!paths)
		return (ft_print_error(cmd, ERR_FILE, NULL));
	cmd_path = ft_check_path(cmd->cmd, paths);
	ft_free_char_array(paths);
	if (!cmd_path)
		return (ft_print_error(cmd, ERR_CMD_NOT, NULL));
	if (cmd->fd->in == RETURN_ERROR)
		return (ft_free_and_ret(cmd_path));
	tmp = ft_realloc("_=", cmd_path, 0, 0);
	ft_change_envp(data, tmp);
	ft_sfree(tmp);
	cmd->pid = fork();
	if (cmd->pid < 0)
		return (ft_print_error(cmd, errno, NULL));
	if (cmd->pid == 0)
		ft_child_process(cmd, data, cmd_path);
	ft_sfree((void *) cmd_path);
	return (0);
}

void	ft_child_process(t_command *cmd, t_data *data, char *cmd_path)
{
	char	**envp;
	char	**argv;

	data->errnum = 0;
	ft_set_child_active();
	ft_connect_pipe(cmd);
	ft_close_child_fd(cmd, data);
	envp = ft_create_envp_array(data->envp);
	argv = ft_create_argv_array(cmd);
	if (access(cmd_path, F_OK | X_OK | R_OK) != RETURN_SUCCESS)
	{
		printf("minishell: %s: Permission denied\n", cmd_path);
		data->errnum = 126;
	}
	execve(cmd_path, argv, envp);
	ft_close_pipe(cmd);
	ft_delete_list(&cmd->argv);
	ft_clear_child_data(data, envp, argv, cmd_path);
	exit(data->errnum);
}

char	**ft_create_argv_array(t_command *cmd)
{
	char	**output;
	t_envp	*tmp;
	int		i;

	output = (char **) ft_malloc((ft_count_of_envp
				(cmd->argv) + 2) * sizeof(char *));
	if (!output)
		return (NULL);
	tmp = cmd->argv;
	output[0] = ft_string_dup(cmd->cmd);
	i = 1;
	while (tmp)
	{
		output[i] = ft_string_dup(tmp->var);
		tmp = tmp->next;
		i++;
	}
	output[i] = NULL;
	return (output);
}

char	**ft_create_envp_array(t_envp *envp)
{
	char	**output;
	t_envp	*tmp;
	int		i;

	output = (char **) ft_malloc((ft_count_of_envp(envp) + 1) * sizeof(char *));
	if (!output)
		return (NULL);
	tmp = envp;
	i = 0;
	while (tmp)
	{
		output[i] = ft_string_dup(tmp->var);
		tmp = tmp->next;
		i++;
	}
	output[i] = NULL;
	return (output);
}

char	*ft_check_path(char *cmd, char **paths)
{
	char	*test_path;
	int		i;

	i = 0;
	if (ft_char_in_str(cmd, '/'))
	{
		if (access(cmd, F_OK) == 0)
			return (ft_string_dup(cmd));
	}
	while (paths && paths[i])
	{
		test_path = ft_realloc(paths[i], "/", 0, 0);
		test_path = ft_realloc(test_path, cmd, 1, 0);
		if (access(test_path, F_OK) == RETURN_SUCCESS)
		{
			return (test_path);
		}
		ft_sfree((void *) test_path);
		i++;
	}
	return (NULL);
}
