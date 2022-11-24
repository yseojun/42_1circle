/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojyang <seojyang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 20:16:18 by seojyang          #+#    #+#             */
/*   Updated: 2022/11/24 21:29:18 by seojyang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

t_line	find_save(t_list *list, int fd)
{
	t_line	new_fd;

	while (list)
	{
		if (fd == list->fd)
			return (list->line);
		list = list->next;
	}
	new_fd.buffer = 0;
	new_fd.read_idx = 0;
	new_fd.read_max_len = 0;
	return (new_fd);
}

void	remove_lst(t_list **list, int fd)
{
	t_list	*save;
	t_list	*search;

	save = *list;
	search = *list;
	while (search)
	{
		if (search->fd == fd)
		{
			save->next = search->next;
			if (save == search)
			{
				if (!search->next)
					*list = 0;
				else
					*list = search->next;
			}
			free(search);
			search = 0;
			return ;
		}
		save = search;
		search = search->next;
	}
}

char	*read_finish(t_line *line, char *output, t_list **list, int fd)
{
	if (line->read_max_len < 0)
	{
		if (output)
			free(output);
		output = 0;
		line->read_idx = 0;
		line->read_max_len = 0;
	}
	free(line->buffer);
	line->buffer = 0;
	remove_lst(list, fd);
	return (output);
}

char	*save_line(char *output, t_list **list, t_line line, int fd)
{
	t_list	*new;
	t_list	*search;

	search = *list;
	if (search)
	{
		while (search)
		{
			if (search->fd == fd)
			{
				search->line = line;
				return (output);
			}
			if (search->next == 0)
				break ;
			search = search->next;
		}
	}
	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
		return (read_finish(&line, output, list, fd));
	new->fd = fd;
	new->line = line;
	new->next = 0;
	if (!search)
		*list = new;
	else
		search->next = new;
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
