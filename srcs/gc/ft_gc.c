/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiraldi <egiraldi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 10:20:42 by mafaussu          #+#    #+#             */
/*   Updated: 2023/02/27 10:43:08 by egiraldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_super_exit(void)
{
	ft_plst_free(&(g_data->gclst));
	ft_write_fd(STDERR_FILENO, "Alloc error\n");
	exit(0);
}

void	*ft_malloc(size_t size)
{
	void	*r;
	t_plst	*item;

	r = malloc(size);
	if (!r)
		ft_super_exit();
	if (!size)
	{
		free(r);
		ft_super_exit();
	}
	item = ft_plst_new(r);
	ft_plst_add(&(g_data->gclst), item);
	return (r);
}

size_t	ft_min(size_t a, size_t b)
{
	if (a < b)
		return (a);
	return (b);
}

void	ft_sfree(void *ptr)
{
	ft_plst_del_one(&(g_data->gclst), ptr);
}
