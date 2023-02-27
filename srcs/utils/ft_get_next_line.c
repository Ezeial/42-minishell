/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiraldi <egiraldi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 08:59:05 by egiraldi          #+#    #+#             */
/*   Updated: 2023/02/27 10:55:35 by egiraldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*ft_gnl_handling(char *buffer, int fd, char *output);
static char	*ft_found_new_line(char *buffer, char *output);

char	*ft_get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*output;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	output = (char *) ft_malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!output)
		return (NULL);
	output[0] = '\0';
	return (ft_gnl_handling(buffer, fd, output));
}

static char	*ft_gnl_handling(char *buffer, int fd, char *output)
{
	ssize_t	read_result;

	while (1)
	{
		if (buffer[0])
		{
			if (ft_char_in_str(buffer, '\n'))
				return (ft_found_new_line(buffer, output));
			output = ft_realloc(output, buffer, 1, 0);
		}
		read_result = read(fd, (void *) buffer, BUFFER_SIZE);
		if ((read_result == -1))
		{
			ft_sfree((void *) output);
			return ((void *) 0);
		}
		buffer[read_result] = '\0';
		if (read_result == 0 && output[0] == 0)
		{
			ft_sfree((void *) output);
			return ((void *) 1);
		}
	}
}

static char	*ft_found_new_line(char *buffer, char *output)
{
	size_t	copy_size;
	char	*tmp;

	copy_size = (ft_char_in_str(buffer, '\n') - buffer) + 1;
	tmp = (char *) ft_malloc((sizeof(char) * copy_size) + 1);
	if (!tmp)
		return (NULL);
	ft_copy(tmp, buffer, copy_size + 1);
	output = ft_realloc(output, tmp, 1, 1);
	ft_copy(buffer, &buffer[copy_size], 0);
	return (output);
}
