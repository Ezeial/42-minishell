/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiraldi <egiraldi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 08:59:47 by egiraldi          #+#    #+#             */
/*   Updated: 2023/02/27 09:10:27 by egiraldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_parser_add_argv(t_data *data, t_parser *parser)
{
	char	*tmp;

	tmp = ft_check_quotes_insert_var(parser, data);
	if (ft_check_for_asterisk(parser, tmp) == RETURN_FALSE)
	{
		if (parser->cmd->cmd)
			ft_lstadd_back(&parser->cmd->argv, ft_lstnew(tmp));
		else
		{
			parser->cmd->cmd = ft_string_dup(tmp);
			parser->cmd->result = RETURN_SUCCESS;
		}
	}
	ft_sfree((void *) tmp);
}
