/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojyang <seojyang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 20:15:33 by seojyang          #+#    #+#             */
/*   Updated: 2022/11/22 23:27:26 by seojyang         ###   ########.fr       */
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
	new_fd.output_len = 0;
	return (new_fd);
}

char	*get_next_line(int fd)
{
	static t_list	*list = 0;
	t_line			line;
	char			*output;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	line = find_save(list, fd);
	output = 0;
	line.output_len = 0;
	if (!line.buffer)
		line.buffer = malloc(BUFFER_SIZE);
	while (1)
	{
		if (line.read_idx == line.read_max_len)
		{
			line.read_idx = 0;
			line.read_max_len = read(fd, line.buffer, BUFFER_SIZE);
		}
		if (line.read_max_len <= 0)
			return (read_finish(&line, output, &list, fd));
		output = join(output, &line);
		if (line.output_len && *(output + line.output_len - 1) == '\n')
			return (save_line(output, &list, line, fd));
	}
}
