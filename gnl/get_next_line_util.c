/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_util.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojyang <seojyang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 20:16:18 by seojyang          #+#    #+#             */
/*   Updated: 2022/11/21 22:09:43 by seojyang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_line	*find_save_or_make(t_line *line, int fd)
{
	t_line	*search;
	t_line	*new;

	search = line;
	while (search)
	{
		if (fd == line->fd)
			return (search);
		search = search->next;
	}
	new = (t_line *)malloc(sizeof(t_line));
	if (!new)
		return (0);
	new->fd = fd;
	new->read_idx = 0;
	new->buffer = 0;
	new->next = 0;
	return (new);
}

void	save_or_delete_line(t_line **save, t_line *line)
{
	t_line	*before_save;

	if (line->buffer)
	{
		if (!*save)
			*save = line;
		while ((*save)->next)
			*save = (*save)->next;
		(*save)->next = line;
	}
	else
	{
		before_save = *save;
		while (*save)
		{
			if ((*save)->fd == line->fd)
			{
				before_save->next = (*save)->next;
				free(save);
			}
			before_save = (*save);
			*save = (*save)->next;
		}
	}
}

int	make_buffer(t_output *output, t_line *line)
{
	ssize_t	read_len;

	line->buffer = (char *)malloc(BUFFER_SIZE);
	if (!line->buffer)
		return (0);
	read_len = read(line->fd, line->buffer, BUFFER_SIZE);
	line->max_read = read_len;
	if (read_len < 0)
		return (0);
	if (read_len == 0)
		output->is_finish = 1;
	return (1);
}

int	make_output(t_output *output, t_line *line)
{
	char	*new;
	ssize_t	to_idx;
	ssize_t	idx;

	to_idx = -1;
	while (output->is_finish || line->read_idx + ++to_idx < line->max_read)
		if (*((char *)line->buffer + line->read_idx + to_idx) == '\n')
			output->is_finish = 1;
	new = malloc(output->output_len + to_idx + 1);
	if (!new)
		return (0);
	idx = -1;
	while (++idx < output->output_len)
		new[idx] = output->line[idx];
	output->output_len += to_idx;
	while (idx < output->output_len)
		new[idx++] = *((char *)line->buffer + line->read_idx++);
	new[idx] = '\0';
	free(output->line);
	output->line = new;
	return (1);
}
