/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojyang <seojyang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 20:15:45 by seojyang          #+#    #+#             */
/*   Updated: 2022/11/22 23:22:33 by seojyang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_line
{
	char		*buffer;
	ssize_t		read_idx;
	ssize_t		read_max_len;
	ssize_t		output_len;
}	t_line;
typedef struct s_list
{
	int				fd;
	struct s_line	line;
	struct s_list	*next;
}	t_list;

char	*get_next_line(int fd);

void	*ft_memcpy(void *dst, const void *src, size_t n);
t_line	*new_line(void);
char	*join(char *output, t_line *line);
char	*read_finish(t_line *line, char *output, t_list **list, int fd);
char	*save_line(char *output, t_list **list, t_line line, int fd);

#endif