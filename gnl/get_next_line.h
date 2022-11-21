/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojyang <seojyang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 20:15:45 by seojyang          #+#    #+#             */
/*   Updated: 2022/11/21 22:08:49 by seojyang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# define BUFFER_SIZE 42

typedef struct s_line
{
	int				fd;
	void			*buffer;
	ssize_t			read_idx;
	ssize_t			max_read;
	struct s_line	*next;
}				t_line;
typedef struct s_output
{
	char		*line;
	ssize_t		output_len;
	int			is_finish;
}	t_output;

char			*get_next_line(int fd);
int		find_finish(t_line *line, t_output *output);

int		make_output(t_output *output, t_line *line);
int		make_buffer(t_output *output, t_line *line);
void		save_or_delete_line(t_line **save, t_line *line);
t_line	*find_save_or_make(t_line *line, int fd);

#endif