/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojyang <seojyang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 20:15:45 by seojyang          #+#    #+#             */
/*   Updated: 2022/11/21 14:53:20 by seojyang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# define BUFFER_SIZE 42

typedef struct s_line
{
	int			fd;
	ssize_t		remain_len;
	void		*remain;
	t_line		*next;
}				t_line;
char	*get_next_line(int fd);

#endif