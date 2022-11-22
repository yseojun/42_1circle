/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojyang <seojyang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 20:16:18 by seojyang          #+#    #+#             */
/*   Updated: 2022/11/22 23:31:16 by seojyang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*join(char *output, t_line *line)
{
	char	*new;
	ssize_t	join_len;

	join_len = 0;
	while (line->read_idx + join_len < line->read_max_len)
	{
		if (*(line->buffer + line->read_idx + join_len) == '\n')
		{
			join_len++;
			break ;
		}
		join_len++;
	}
	new = malloc(line->output_len + join_len + 1);
	if (!new)
		return (0);
	ft_memcpy(new, output, line->output_len);
	ft_memcpy(new + line->output_len, line->buffer + line->read_idx, join_len);
	new[line->output_len + join_len] = 0;
	line->output_len += join_len;
	line->read_idx += join_len;
	free(output);
	return (new);
}

char	*read_finish(t_line *line, char *output, t_list **list, int fd)
{
	t_list	*save;

	if (line->read_max_len < 0)
	{
		if (output)
			free(output);
		output = 0;
	}
	free(line->buffer);
	line->buffer = 0;
	save = *list;
	while (*list)
	{
		if ((*list)->fd == fd)
		{
			save = (*list)->next;
			free(*list);
			*list = 0;
			return (output);
		}
		save = *list;
		*list = (*list)->next;
	}
	return (output);
}

char	*save_line(char *output, t_list **list, t_line line, int fd)
{
	t_list	*new;

	if (line.read_idx == line.read_max_len)
		return (read_finish(&line, output, list, fd));
	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
		return (read_finish(&line, output, list, fd));
	new->fd = fd;
	new->line = line;
	new->next = 0;
	if (!*list)
		*list = new;
	else
	{
		while ((*list)->next)
			*list = (*list)->next;
		(*list)->next = new;
	}
	return (output);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	idx;

	if (!dst && !src)
		return (0);
	idx = 0;
	while (idx < n)
	{
		*((unsigned char *) dst + idx) = *((unsigned char *) src + idx);
		idx++;
	}
	return (dst);
}
