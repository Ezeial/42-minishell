/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiraldi <egiraldi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 09:07:09 by egiraldi          #+#    #+#             */
/*   Updated: 2023/02/27 13:22:10 by egiraldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_envp	*ft_copy_envp(char **envp)
{
	t_envp	*output;
	int		i;

	output = ft_lstnew(envp[0]);
	if (!output)
		return (0);
	i = 1;
	while (envp[i])
	{
		if (!ft_lstadd_back(&output, ft_lstnew(envp[i])))
		{
			ft_delete_list(&output);
			return (0);
		}
		i++;
	}
	return (output);
}

t_envp	*ft_lstnew(char *content)
{
	t_envp	*new_element;

	new_element = (t_envp *) ft_malloc(sizeof(t_envp));
	if (!new_element)
		return (NULL);
	new_element->var = ft_string_dup(content);
	if (!new_element->var)
	{
		ft_sfree(new_element);
		return (NULL);
	}
	new_element->next = NULL;
	return (new_element);
}

t_envp	*ft_lstlast(t_envp *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

t_envp	*ft_lstadd_back(t_envp **lst, t_envp *new)
{
	if (!*lst)
		*lst = new;
	else
		ft_lstlast(*lst)->next = new;
	return (new);
}

void	ft_delete_list(t_envp **lst)
{
	t_envp	*tmp;

	while (*lst)
	{
		tmp = *lst;
		*lst = (*lst)->next;
		ft_sfree((void *) tmp->var);
		ft_sfree((void *) tmp);
	}
	*lst = NULL;
}
