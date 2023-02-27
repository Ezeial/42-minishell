/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_plst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiraldi <egiraldi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 10:20:48 by mafaussu          #+#    #+#             */
/*   Updated: 2023/02/27 11:37:12 by egiraldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_plst	*ft_plst_new(void *data)
{
	t_plst	*r;

	r = malloc(sizeof(t_plst));
	if (!r)
	{
		ft_super_exit();
	}
	r->data = data;
	r->next = 0;
	return (r);
}

void	ft_plst_add(t_plst **l, t_plst *i)
{
	t_plst	*it;

	it = *l;
	if (!it)
	{
		*l = i;
		return ;
	}
	while (it)
	{
		if (!it->next)
		{
			it->next = i;
			return ;
		}
		it = it->next;
	}
}

t_plst	*ft_plst_find(t_plst *l, void *d)
{
	t_plst	*it;

	it = l;
	while (it)
	{
		if (it->data == d)
			return (it);
		it = it->next;
	}
	return (0);
}

void	ft_plst_del_one(t_plst **l, void *d)
{
	t_plst	*it;
	t_plst	*prev;

	if (!(*l))
		return ;
	if ((*l)->data == d)
		return (ft_handle_first(l));
	it = (*l)->next;
	prev = *l;
	while (it)
	{
		if (it->data == d)
		{
			prev->next = it->next;
			free(it->data);
			free(it);
			return ;
		}
		prev = it;
		it = it->next;
	}
}

void	ft_plst_free(t_plst **l)
{
	t_plst	*it;
	t_plst	*swp;

	it = *l;
	while (it)
	{
		swp = it->next;
		free(it->data);
		free(it);
		it = swp;
	}
	*l = 0;
}
