/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojyang <seojyang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 20:15:33 by seojyang          #+#    #+#             */
/*   Updated: 2022/11/21 16:58:09 by seojyang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*edit_buffer(char *buffer, ssize_t read_len)
{
	char	*new;
	ssize_t	idx;
	ssize_t	new_idx;

	idx = 0;
	while (idx < read_len)
	{
		if (buffer[idx] == '\n')
			break ;
		idx++;
	}
	if (idx == read_len)
		return (buffer);
	new = malloc(read_len - idx - 1);
	if (!new)
		return (0);
	new_idx = 0;
	while (new_idx < read_len - idx - 1)
		new[new_idx] = buffer[idx + 1 + new_idx];
	return (new);
}

char	*edit_output(char *output, char *buffer, \
		ssize_t output_len, ssize_t read_len)
{
	char	*new;
	ssize_t	idx;

	new = malloc(output_len + read_len + 1);
	while (idx < output_len)
	{
		new[idx] = output[idx];
		idx++;
	}
	while (idx < read_len)
	{
		new[output_len + idx] = buffer[idx];
		idx++;
	}
	free(output);
	return (new);
}

char	*get_next_line(int fd)
{
	static t_line	*line;
	char			*output;
	char			*buffer;
	ssize_t			output_len;
	ssize_t			read_len;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	while ()
	{
		buffer = malloc(BUFFER_SIZE);
		if (!buffer)
			return (0);
		read_len = read(fd, buffer, BUFFER_SIZE);
		if (read_len < 0)
			return (0);
		if (read_len == 0)
			return (output);
		output_len += read_len;
		output = edit_output(output, buffer, output_len, read_len);
		edit_buffer(buffer, read_len);
	}
	return (output);
}
