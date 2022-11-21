/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojyang <seojyang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 20:15:33 by seojyang          #+#    #+#             */
/*   Updated: 2022/11/21 22:08:30 by seojyang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	find_finish(t_line *line, t_output *output)
{
	if (!line->buffer)
		if (!make_buffer(output, line))
			return (0);
	if (!make_output(output, line))
		return (0);
	if (line->read_idx == line->max_read)
	{
		free(line->buffer);
		line->buffer = 0;
	}
	return (1);
}

char	*get_next_line(int fd)
{
	static t_line	*save;
	t_line			*line;
	t_output		output;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	output.output_len = 0;
	output.is_finish = 0;
	line = find_save_or_make(save, fd);
	if (!line)
		return (0);
	while (!output.is_finish)
		if (!find_finish(line, &output))
			return (0);
	save_or_delete_line(&save, line);
	return ((char *)output.line);
}
