/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wildcard1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiraldi <egiraldi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 09:07:38 by egiraldi          #+#    #+#             */
/*   Updated: 2023/02/27 09:10:27 by egiraldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_envp	*ft_prepare_list(char *input)
{
	t_envp	*full_list;
	t_envp	*new_list;
	char	**filter_array;
	char	*path;
	char	*filter;

	ft_get_filter_path(input, &path, &filter);
	full_list = ft_get_files(path);
	filter_array = ft_get_filter(filter);
	new_list = ft_apply_filter(full_list, filter_array);
	ft_free_char_array(filter_array);
	ft_delete_list(&full_list);
	return (new_list);
}

void	ft_get_filter_path(char *input, char **path, char **filter)
{
	int		slash;

	slash = ft_last_pos_in_string(input, '/');
	if (slash >= 0)
	{
		*path = ft_get_substring(input, 0, slash + 1);
		*filter = ft_string_dup(&input[slash + 1]);
	}
	else
	{
		*path = ft_string_dup(".");
		*filter = ft_string_dup(input);
	}
}
